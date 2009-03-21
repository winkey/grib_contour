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
#include <libkml/libKML.h>
#include <libogr2kml/libogr2kml.h>

#include "options.h"
#include "color.h"
#include "grib.h"
#include "color.h"
#include "ogrcode.h"
#include "gdalcode.h"
#include "contour.h"
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
		
		
		ds2kml(hDS, o->kmzfile);
	
	}
	
	/***** translate first *****/
	else {
		
		/***** get the ogr driver *****/
		
		OGRSFDriverH hMemDriver = get_driver("Memory");
		
		/***** create the datasource *****/
		
		OGRDataSourceH hogrDS2 = create_datasource(hMemDriver, "hDS2");
		
		/***** add a style table to the dataset *****/
		
		add_ds_style(hDS, cscales);
		
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
		
		ds2kml(hogrDS2, o->kmzfile);
		
		/***** cleanup *****/
		
		OSRDestroySpatialReference(hSRS2);
		OGR_DS_Destroy(hogrDS2);
		
	}

	
	/***** cleanup *****/
		
//	OSRDestroySpatialReference(hSRS2);
	
}
