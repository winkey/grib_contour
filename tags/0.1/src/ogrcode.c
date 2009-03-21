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
		
	if (!(hDS = OGR_Dr_CreateDataSource( hDriver, dst_file, NULL ))) {
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
	
	if (!(hLayer = OGR_DS_CreateLayer(hDS, name, hSRS, wkbLineString, NULL))) {
		fprintf(stderr, "ERROR: Unable to create layer\n");
		exit(EXIT_FAILURE);
	}
	
	return hLayer;
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
		fprintf(stderr, "WARNING: Failed to transform feature %ld.\n",
						OGR_F_GetFID(hDstFeat));
	}
	
	return;
}

		