/***************************************************************************
 *            ogrcode.h
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
 
#ifndef _OGRCODE_H
#define _OGRCODE_H

#include <gdal.h>
#include <cpl_conv.h>
#include <ogr_api.h>
#include <ogr_srs_api.h>


/*******************************************************************************
	function to get the spacial referance from a raster
	
	args:
							band		gdal raster band
	
	returns:
							ogr spatial reference
*******************************************************************************/

OGRSpatialReferenceH get_srs(
	GDALDatasetH hband);

/*******************************************************************************
	function to fetch a ogr driver

	args:
						driver		the name of the ogr driver
	
	returns:
						OGRSFDriverH
*******************************************************************************/

OGRSFDriverH get_driver(
	char *driver);

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
	char *dst_file);

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
	OGRwkbGeometryType type);


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
	OGRLayerH hLayer);

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
	OGRSpatialReferenceH hDstSRS);

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
	OGRFeatureH hSrcFeat);

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
	OGRCoordinateTransformationH *hTransform);

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
	OGRFeatureH hDstFeat);

void getpoints (
	OGRFeatureH hFeat,
	buffer *points);

void transform(
	OGRSpatialReferenceH hsrcSRS,
	OGRLayerH hsrcLayer,
	OGRSpatialReferenceH hdstSRS,
	OGRLayerH hdstLayer);
	
#endif /* _OGRCODE_H */
