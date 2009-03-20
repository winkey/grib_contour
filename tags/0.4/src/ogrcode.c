/***************************************************************************
 *            ogrcode.c
 *
 *  Wed Jan 16 11:25:01 2008
 *  Copyright  2008  winkey
 *  <rush@winkey.org>
 ****************************************************************************/

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

#include "grib.h"
#include "buffer.h"
#include "ogrcode.h"

#define DEBUG 0

/*******************************************************************************
	function to get the spacial referance from a raster
	
	args:
							band		gdal raster band
	
	returns:
							ogr spatial reference
*******************************************************************************/

OGRSpatialReferenceH get_srs(
	GDALDatasetH hband)
{
	OGRSpatialReferenceH hSRS = NULL;
	
	const char *wkt = GDALGetProjectionRef(hband);
	
	if(wkt && *wkt)
		hSRS = OSRNewSpatialReference(wkt);
	
	return hSRS;
}

/*******************************************************************************
	function to fetch a ogr driver

	args:
						driver		the name of the ogr driver
	
	returns:
						the ogr driver
*******************************************************************************/

OGRSFDriverH get_driver(
	char *driver)
{
	
	OGRSFDriverH hDriver = NULL;
	
	if(!(hDriver = OGRGetDriverByName(driver))) {
		fprintf(stderr, "ERROR: Unable to find the %s driver\n", driver);
		exit(EXIT_FAILURE);
	}
	
	return hDriver;
}

/*******************************************************************************
	create the ogr output data source
	
	args:
						hDriver			the ogr driver
						dst_file		the destination file name
	
	returns:
						the ogr data source
*******************************************************************************/

OGRDataSourceH create_datasource(
	OGRSFDriverH hDriver,
	char *dst_file)
{
	OGRDataSourceH hDS = NULL;
		
	if (!(hDS = OGR_Dr_CreateDataSource(hDriver, dst_file, NULL))) {
		fprintf(stderr, "ERROR: Unable to to create data source: %s\n", dst_file);
		exit(EXIT_FAILURE);
	}
	
	return hDS;
}

/*******************************************************************************
	function to create the ogr layer
	
	args:
							hDS			the ogr datasource
							name		the name of the layer
							hSRS		the spatial reference
							type		the geometry type
	
	returns:
							a new ogr layer
*******************************************************************************/

OGRLayerH create_layer(
	OGRDataSourceH hDS,
	const char *name,
	OGRSpatialReferenceH hSRS,
	OGRwkbGeometryType type)
{
	OGRLayerH hLayer;
	
	if (!(hLayer = OGR_DS_CreateLayer(hDS, name, hSRS, type, NULL))) {
		fprintf(stderr, "ERROR: Unable to create layer\n");
		exit(EXIT_FAILURE);
	}
	
	return hLayer;
}

/*******************************************************************************
	function to create a ogr field
	
	args:
							name				the name of the field to create
							eType				the field data type
							width				the field data width
							precision		the field data precision
							hLayer			the layer to create the field in
	
	returns:
							nothing
*******************************************************************************/

void create_field(
	const char *name,
	OGRFieldType eType,
	int width,
	int precision,
	OGRLayerH hLayer)
{

	OGRFieldDefnH hFld = OGR_Fld_Create(name, eType);
	OGR_Fld_SetWidth(hFld, width);
	if (eType != OFTInteger)
		OGR_Fld_SetPrecision(hFld, precision);
	OGR_L_CreateField(hLayer, hFld, FALSE);
	OGR_Fld_Destroy(hFld);

	return;
}
	
/*******************************************************************************
	function to set up coord transformation
	
	args:
						hSrcSRS the source spatial reference
						hDstSRS the destination spatial reference

	returns:
						a new coordanate transformation
*******************************************************************************/

OGRCoordinateTransformationH *create_coord_transform(
	OGRSpatialReferenceH hSrcSRS,
	OGRSpatialReferenceH hDstSRS)
{																									
	OGRCoordinateTransformationH *hTransform = NULL;
	
	if (!(hTransform = OCTNewCoordinateTransformation(hSrcSRS, hDstSRS))) {
		fprintf (stderr, "ERROR can't create transformation\n");
		exit(EXIT_FAILURE);
	}
		
	char *wkt;
	
	OSRExportToWkt(hSrcSRS, &wkt);
	if (DEBUG) fprintf(stderr, "SrcWKT =\n%s\n\n", wkt);
	
	OSRExportToWkt(hDstSRS, &wkt);
	if (DEBUG) fprintf(stderr, "DstWKT =\n%s\n\n", wkt);
	
	return hTransform;
}

/*******************************************************************************
	function to translate a feature from one ogr format to another
	
	args:
							hDstFeat		the destination feature
							hSrcFeat		the source feature

	returns:
							nothing
*******************************************************************************/

void translate_feature(
	OGRFeatureH hDstFeat,
	OGRFeatureH hSrcFeat)
{
	
	if (OGR_F_SetFrom(hDstFeat, hSrcFeat, TRUE) != OGRERR_NONE) {
		fprintf(stderr, "WARNING: Unable to translate feature %ld\n",
						OGR_F_GetFID(hSrcFeat));
	}
	
	return;
}

/*******************************************************************************
	function to transform the geometry of a feature
	
	args:
							hDstFeat		the destination feature
							hTransform	the transformer
	returns:
							nothing
*******************************************************************************/

void transform_feature(
	OGRFeatureH hDstFeat,
	OGRCoordinateTransformationH *hTransform)
{
	OGRGeometryH *Dstgeom = NULL;
	
	if ((Dstgeom = OGR_F_GetGeometryRef(hDstFeat))) {
		if (OGRERR_NONE != OGR_G_Transform(Dstgeom, hTransform)) {
			fprintf(stderr, "WARNING: Failed to transform feature %ld.\n",
							OGR_F_GetFID(hDstFeat));
		}
	}
	
	return;
}

/*******************************************************************************
	function to add a new feature to a layer
	
	args:
							hDstLayer		the layer to add a new feature too
							hDstFeat		the feature to add
	returns:
							nothing
*******************************************************************************/

void add_feature(
	OGRLayerH hDstLayer,
	OGRFeatureH hDstFeat)
{
	
	if (OGR_L_CreateFeature(hDstLayer, hDstFeat) != OGRERR_NONE) {
		fprintf(stderr, "WARNING: Failed to add feature %ld.\n",
						OGR_F_GetFID(hDstFeat));
	}
	
	return;
}

		
void getpoint (
	OGRGeometryH	hGeom,
	int pointnum,						 
	buffer *points)
{
	double x,y,z;
	
	OGR_G_GetPoint(hGeom, pointnum, &x, &y, &z);
	
	if (x > 180)
		x -= ((int) ((x+180)/360)*360);
	else if (x < -180)
		x += ((int) (180 - x)/360)*360;
	
	buffer_printf(points, "%.4lg,%.4lg ", x, y);
	
	return;
}

void getpoints (
	OGRFeatureH hFeat,
	buffer *points)
{
	int i;
	OGRGeometryH hGeom = OGR_F_GetGeometryRef(hFeat);
	int numpoints = OGR_G_GetPointCount(hGeom);
	
	for (i = 0 ; i < numpoints ; i++)
		getpoint(hGeom, i, points);
	
	return;
}

void transform(
	OGRSpatialReferenceH hsrcSRS,
	OGRLayerH hsrcLayer,
	OGRSpatialReferenceH hdstSRS,
	OGRLayerH hdstLayer)
{

	/***** Setup coordinate transformation *****/
	
	OGRCoordinateTransformationH *hTransform = 
		create_coord_transform(hsrcSRS, hdstSRS);
	
	/***** reset the source layer *****/
	
	OGR_L_ResetReading(hsrcLayer);
	
	/***** loop while theres features *****/
	
	OGRFeatureH hsrcFeat;
	
	while((hsrcFeat = OGR_L_GetNextFeature(hsrcLayer))) {
		
		CPLErrorReset();
		
		/***** make a new feature *****/
		
		OGRFeatureH hdstFeat = OGR_F_Create(OGR_L_GetLayerDefn(hdstLayer));
		
		/***** translate feature *****/
		
		translate_feature(hdstFeat, hsrcFeat);
		
		
		/***** transform the feature if it translated *****/
		
		transform_feature(hdstFeat, hTransform);
		
		CPLErrorReset();
		
		/***** create the new feature in the layer *****/
		
		add_feature(hdstLayer, hdstFeat);
		
		/***** cleanup *****/
		
		OGR_F_Destroy(hsrcFeat);
		OGR_F_Destroy(hdstFeat);
	}
	
	/***** cleanup *****/
	
	OCTDestroyCoordinateTransformation(hTransform);
	
	return;
}
