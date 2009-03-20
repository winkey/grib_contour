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
 
#ifndef _GDALCODE_H
#define _GDALCODE_H

#include <gdal.h>

/*******************************************************************************
	function to open the raster file
	
	Args:
						float			pointer to the float to open
						width			width of the raster in pixels
						height		height of the raster in lines
	
	returns:
						the gdal dataset
*******************************************************************************/

GDALDatasetH raster_open_mem(
	float *raster,
	int width,
	int height);

/*******************************************************************************
	function to set the raster projection
	
	args:
						hDS			the gdal dataset
						gds			the grib gds info struct
	
	returns:
						nothing
				
*******************************************************************************/

OGRSpatialReferenceH set_projection(
	GDALDatasetH *hDS,
	gds_t *gds);

/*******************************************************************************
	function to get the raster band
	
	args:
						hDS				gdal dataset
						band_num	the band number
	
	returns:
						the gdal raster band
*******************************************************************************/

GDALRasterBandH get_band(
	GDALDatasetH hDS,
	int band_num);

GDALDatasetH do_gdal(
	float *raster,
	gds_t *gds,
	OGRSpatialReferenceH *hSrcSRS,
	GDALRasterBandH *hBand);

/*******************************************************************************
	function to get a gdal driver by its name
	
	args:
						name			the name of the driver
	
	returns:
						the gdal driver
*******************************************************************************/

GDALDriverH gdal_get_driver_by_name (
	char *name);

#endif /* _GDALCODE_H */

 
