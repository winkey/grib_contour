/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor Boston, MA 02110-1301,  USA
 */

#include <stdio.h>
#include <stdlib.h>
#include <gdal_alg.h>
#include <libKML/libKML.h>
#include <libogr2kml/libogr2kml.h>

#include "options.h"
#include "color.h"
#include "grib.h"
#include "color.h"
#include "ogrcode.h"
#include "gdalcode.h"
#include "contour.h"
#include "hilo.h"
#include "style.h"
#include "style.h"
#include "error.h"



void contour (
	GDALDatasetH hgdalDS,
	OGRSpatialReferenceH hSRS,
	OGRDataSourceH *hogrDS,
	OGRLayerH *hLayer,
	options *o,
	int id,
	int elev,
	gds_t *gds,
	color_scale *cscales)
{
	/***** get the raster band *****/
	
	GDALRasterBandH hBand = get_band(hgdalDS, 1);
	
	/***** get the ogr driver *****/
	
	OGRSFDriverH hMemDriver = get_driver("Memory");
	
	/***** create the datasource *****/
	
	*hogrDS = create_datasource(hMemDriver, "hMemDS");
	
	/***** create the layer *****/
	
	*hLayer = create_layer(*hogrDS, "contour", hSRS, wkbLineString);
	
	/***** id field *****/
	
	create_field("ID", OFTInteger, 8, 0, *hLayer);
	
	/***** value field *****/
	
	create_field("elev", OFTReal, 12, 3, *hLayer);
	
	/***** contour *****/
	
	if (!o->finterval) {
		GDALContourGenerate(hBand, o->interval, 0.0, 0, NULL,
												gds->missing, gds->missing_value,
												*hLayer, id, elev, NULL, NULL);
	}
	else {
		color_scale *scale;
		int num_fintervals = 0;
		double *fintervals;
		int i;
		
		/**** count the intervals ****/
			
		for (scale = cscales ; *(scale->color) != 0 ; scale++)
			num_fintervals++;
		
		/***** alocate *****/
		
		if (!(fintervals = malloc(num_fintervals * sizeof(fintervals))))
			ERROR("contour");
		
		/***** copy *****/
		
		for (i = 0, scale = cscales ; *(scale->color) != 0; scale++, i++)
			fintervals[i] = scale->value;
		
		/***** contour *****/
		
		GDALContourGenerate(hBand, 0, 0.0, num_fintervals, fintervals,
												gds->missing, gds->missing_value,
												*hLayer, id, elev, NULL, NULL);
	}
	
	return;
}

void contour2kml(
	gds_t *gds,
	options *o,
	color_scale *cscales,
	OGRSpatialReferenceH hSRS,
	OGRDataSourceH hDS,
	OGRLayerH hLayer)
{
	
	/***** style all the features in the layer *****/
	/***** if the dataset gets trasnformed this will be copyed *****/
	
	add_features_style(hLayer, cscales);
		
	/***** check to see if it needs transformed *****/
	
	if (gds->proj == GDS_LATLON || gds->proj == GDS_GAUSSIAN_LATLON) {
		
		/***** add a style table to the dataset *****/
		
		add_ds_style(hDS, cscales);
		
		if (o->hilo)
			hilo(hDS, hLayer, hSRS);
		
		ds2kml(hDS, o->kmzfile);
	
	}
	
	/***** translate first *****/
	else {
		
		/***** get the ogr driver *****/
		
		OGRSFDriverH hMemDriver = get_driver("Memory");
		
		/***** create the datasource *****/
		
		OGRDataSourceH hogrDS2 = create_datasource(hMemDriver, "hDS2");
		
		/***** add a style table to the dataset *****/
		
		add_ds_style(hogrDS2, cscales);
		
		/***** set the spatial reference for kml *****/
	
		OGRSpatialReferenceH hSRS2 = OSRNewSpatialReference(NULL);
		OSRSetWellKnownGeogCS(hSRS2, "WGS84");
		
		/***** create the layer to trasnslate too *****/
		
		OGRLayerH hLayer2 = create_layer(hogrDS2, "contour", hSRS2, wkbLineString);
		
		/***** id field *****/
	
		create_field("ID", OFTInteger, 8, 0, hLayer2);
		
		/***** value field *****/
		
		create_field("elev", OFTReal, 12, 3, hLayer2);
		
		/***** transform *****/
		
		transform(hSRS, hLayer, hSRS2, hLayer2);
		
		if (o->hilo)
			hilo(hogrDS2, hLayer2, hSRS2);
		
		ds2kml(hogrDS2, o->kmzfile);
		
		/***** cleanup *****/
		
		OSRDestroySpatialReference(hSRS2);
		OGR_DS_Destroy(hogrDS2);
		
	}

	
	/***** cleanup *****/
		
//	OSRDestroySpatialReference(hSRS2);
	
}

OGRLayerH contour2pg_GetLayer(
	OGRDataSourceH hDS,
	OGRSpatialReferenceH hSRS_dst,
	options *o)
{
	OGRLayerH hPGLayer;
	
	if (!(hPGLayer = OGR_DS_GetLayerByName(hDS, o->scalename))) {
		if (!(hPGLayer = OGR_DS_CreateLayer(hDS, o->scalename, hSRS_dst, wkbLineString, NULL)))
			ERROR("can not create new layer");
		
		/***** create the run field *****/
		
		OGRFieldDefnH hField = OGR_Fld_Create("run", OFTDateTime);
		OGR_L_CreateField(hPGLayer, hField, FALSE);
		OGR_Fld_Destroy(hField);
		
		/***** create the forecast hour field *****/
		
		hField = OGR_Fld_Create("hour", OFTInteger);
		OGR_L_CreateField(hPGLayer, hField, FALSE);
		OGR_Fld_Destroy(hField);
		
		/***** create the date field *****/
		
		hField = OGR_Fld_Create("begin", OFTDateTime);
		OGR_L_CreateField(hPGLayer, hField, FALSE);
		OGR_Fld_Destroy(hField);
		
		hField = OGR_Fld_Create("end", OFTDateTime);
		OGR_L_CreateField(hPGLayer, hField, FALSE);
		OGR_Fld_Destroy(hField);
		
		/***** create the value field *****/
		
		hField = OGR_Fld_Create("value", OFTReal);
		OGR_L_CreateField(hPGLayer, hField, FALSE);
		OGR_Fld_Destroy(hField);
		
	}
	
	return hPGLayer;
}

void contour2pg_SetSTyleTable(
	OGRLayerH hPGLayer,
	color_scale *cscales)
{
															
	/***** if the layer already has a style table no need to do it again *****/
	
	//OGRStyleTableH hSTBL = OGR_L_GetStyleTable(hPGLayer);
	
	//if (!hSTBL) {
		//OGR_STBL_Destroy(hSTBL);
		
		/***** set the style table *****/
		
		OGRStyleTableH hSTBL = OGR_STBL_Create();
		OGRStyleMgrH hSM = OGR_SM_Create(hSTBL);
		
		color_scale *cscale;
		for (cscale = cscales ; *(cscale->color) ; cscale++) {
			
			/***** clear the current style in the manager *****/
			
			OGR_SM_InitStyleString(hSM, NULL);
			
			char color[10] = {};
			OGRStyleToolH hST;
			
			/***** pen color *****/
			
			snprintf(color, sizeof(color), "#%sff", cscale->color);
			
			hST = OGR_ST_Create(OGRSTCPen);
			OGR_ST_SetParamStr(hST, OGRSTPenColor, color);
			OGR_ST_SetParamNum(hST,OGRSTPenWidth, 1); 
			OGR_ST_SetUnit(hST, OGRSTUPixel, 2);
			OGR_SM_AddPart (hSM, hST);
			OGR_ST_Destroy(hST);
			
			/***** brush color *****/
			
			snprintf(color, sizeof(color), "#%saa", cscale->color);
			hST = OGR_ST_Create(OGRSTCBrush);
			OGR_ST_SetParamStr(hST, OGRSTBrushFColor, color);
			OGR_SM_AddPart (hSM, hST);
			OGR_ST_Destroy(hST);
			
			/***** add the style in the manager to the style table *****/
			
			snprintf(color, sizeof(color), "@%s", cscale->color);
			OGR_SM_AddStyle(hSM, color, NULL);
			
		}
		
		OGR_SM_Destroy(hSM);
		OGR_L_SetStyleTable(hPGLayer, hSTBL);
	//}
	
	/**** cleanup *****/
	
	OGR_STBL_Destroy(hSTBL);
}

void contour2pg(
	gds_t *gds,
	options *o,
	color_scale *cscales,
	OGRSpatialReferenceH hSRS,
	OGRDataSourceH hDS,
	OGRLayerH hLayer)
{
	
	/***** get the ogr driver *****/
	
	OGRSFDriverH hPGDriver = get_driver("PostgreSQL");
	
	/***** open the pg ds *****/
	
	OGRDataSourceH hPGDS = OGR_Dr_Open(hPGDriver, o->pgfile, 1);
	
	/***** set the output SRS *****/
	
	OGRSpatialReferenceH hSRS_dst = OSRNewSpatialReference(NULL);
	OSRSetWellKnownGeogCS(hSRS_dst, "WGS84");
	
	/***** get the layer *****/
		
	OGRLayerH hPGLayer = contour2pg_GetLayer(hPGDS, hSRS_dst, o);
		
	/***** set the style table *****/
	
	contour2pg_SetSTyleTable(hPGLayer, cscales);
	
	/***** if the projection is not latlon create a transformer *****/
	
	OGRCoordinateTransformationH *hTransform = NULL;
	
	if (gds->proj != GDS_LATLON && gds->proj != GDS_GAUSSIAN_LATLON) {
		if (!(hTransform = OCTNewCoordinateTransformation(hSRS, hSRS_dst)))
			ERROR("Can't create transformation");
	}
	
	/***** loop while theres features *****/
	
	OGRFeatureDefnH hPGFeatDef = OGR_L_GetLayerDefn(hPGLayer);
	
	OGRFeatureH hFeat;
	OGR_L_ResetReading(hLayer);

	while((hFeat = OGR_L_GetNextFeature(hLayer))) {
		
		/***** create a new pg feature *****/
		
		OGRFeatureH hPGFeat;
		if (!(hPGFeat = OGR_F_Create (hPGFeatDef)))
			ERROR("Can't create new feature");
		
		/***** get the geometry *****/
		
		OGRGeometryH hGeom = OGR_F_GetGeometryRef(hFeat)   	;
		
		/***** check to see if it needs transformed *****/
	
		if (hTransform)
			OGR_G_Transform(hGeom, hTransform);
		
		/***** make sure its -180 to 180 *****/
		
		int i;
		int numpoints = OGR_G_GetPointCount(hGeom);
	
		for (i = 0 ; i < numpoints ; i++) {
			double x, y, z;
			OGR_G_GetPoint(hGeom, i, &x, &y, &z);
	
			if (x > 180)
				x -= 360;
			else if (x < -180)
				x += 360;
	
			OGR_G_SetPoint(hGeom, i, x, y, z);
		
		}
		
		/***** write the geometry *****/
		
		OGR_F_SetGeometryDirectly(hPGFeat, hGeom);
		
		/***** run *****/
		
		int fldidx = OGR_FD_GetFieldIndex(hPGFeatDef, "run");
		OGR_F_SetFieldDateTime(hPGFeat,	fldidx, o->run.tm_year + 1900,
													 o->run.tm_mon + 1, o->run.tm_mday, 
													 o->run.tm_hour, 0, 0, 100);
			
		/***** hour *****/
		
		fldidx = OGR_FD_GetFieldIndex(hPGFeatDef, "hour");
		OGR_F_SetFieldInteger (hPGFeat, fldidx, o->hour);
		
		/***** begin *****/
		
		fldidx = OGR_FD_GetFieldIndex(hPGFeatDef, "begin");
		
		OGR_F_SetFieldDateTime(hPGFeat,	fldidx, o->begin.tm_year + 1900,
													 o->begin.tm_mon + 1, o->begin.tm_mday, 
													 o->begin.tm_hour, 0, 0, 100);
			
		/***** end *****/
		
		fldidx = OGR_FD_GetFieldIndex(hPGFeatDef, "end");
		
		OGR_F_SetFieldDateTime(hPGFeat,	fldidx, o->end.tm_year + 1900,
													 o->end.tm_mon + 1, o->end.tm_mday, 
													 o->end.tm_hour, 0, 0, 100);
			
		/***** value *****/
		
		fldidx = OGR_FD_GetFieldIndex(hPGFeatDef, "value");
		OGR_F_SetFieldDouble (hPGFeat, fldidx, OGR_F_GetFieldAsDouble(hFeat, 1));
		
		/***** set the style string *****/
			
		char name[20] = {};
		snprintf(name, sizeof(name), "@%s",
						 color_checkscale(cscales, OGR_F_GetFieldAsDouble(hFeat, 1)));
		OGR_F_SetStyleString(hPGFeat, name);
			
		/***** add the feature to a layer *****/
			
		OGR_L_CreateFeature(hPGLayer, hPGFeat);
		
		/***** cleanup *****/
		
		OGR_F_Destroy(hFeat);

		
	}
	
	/***** cleanup *****/
	
	if (hTransform)
		OCTDestroyCoordinateTransformation(hTransform);
	
	OGR_DS_Destroy(hPGDS);
	OSRDestroySpatialReference(hSRS_dst);
	
	
}
