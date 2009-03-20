/***************************************************************************
 *            gdalcode.c
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
#include <gdal.h>
#include <gdal_alg.h>
#include <cpl_conv.h>
#include <ogr_api.h>
#include <ogr_srs_api.h>

#include "grib.h"
#include "gdalcode.h"
#include "error.h"

#define DEBUG 0

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
	int height)
{
	GDALDatasetH result = NULL;
	char myfilename[300];
	
	snprintf(myfilename, sizeof(myfilename),
					 "MEM:::DATAPOINTER=%p,PIXELS=%i,LINES=%i,BANDS=1,DATATYPE=Float32",
					 raster, width, height);
	
	if (!(result = GDALOpen(myfilename, GA_ReadOnly)))
		ERROR("raster_open");
	
	return result;
}

/*******************************************************************************
	function to transform the origins to the units the projection uses
*******************************************************************************/

void transform_origin(
	OGRSpatialReferenceH hSrcSRS,
	OGRSpatialReferenceH hDstSRS,
	double *MinX,
	double *MaxY)
{
											
	OGRCoordinateTransformationH transform = NULL;
	
	if (!(transform = OCTNewCoordinateTransformation(hSrcSRS, hDstSRS)))
		fprintf(stderr, "WARNING: failed to create Transformation\n");
	else {
		if (!OCTTransform(transform, 1, MinX, MaxY, NULL))
			fprintf(stderr, "WARNING: Transformation failed\n");
		
		OCTDestroyCoordinateTransformation(transform);
	}
	
	return;
}

/*******************************************************************************
	function to set the projection in the gdal dataset
*******************************************************************************/

void gdal_set_projection(
	GDALDatasetH hDS,
	OGRSpatialReferenceH hSRS)
{
	char *wkt;
	
	OSRExportToWkt(hSRS, &wkt);
	if (DEBUG) fprintf (stderr, "%s\n", wkt);
	GDALSetProjection(hDS, wkt);
	
	free (wkt);
	return;
}

/*******************************************************************************
	function to set the raster geotransform
	
	Args:
						ds				gdal dataset
						xo				x origin
						xsize			x pixel size
						xrot			x rotation
						yo				y origin
						ysize			y pixel size
						yrot			y rotation
	
	returns:
						nothing
*******************************************************************************/

void set_geotransform(
	GDALDatasetH hDS,
	double xo,
	double xsize,
	double xrot,
	double yo,
	double ysize,
	double yrot)


{
	double padfTransform[6];
	
	padfTransform[0] = xo;     /* X Origin (top left corner) */
	padfTransform[1] = xsize;      /* X Pixel size */
	padfTransform[2] = xrot;
	padfTransform[3] = yo;     /* Y Origin (top left corner) */
	padfTransform[4] = yrot;     
	padfTransform[5] = ysize;      /* Y Pixel Size */
	
	GDALSetGeoTransform(hDS, padfTransform);
	
	if (DEBUG) {
		if(padfTransform[2] == 0.0 && padfTransform[4] == 0.0) {
			fprintf(stderr, "Origin = (%.15f,%.15f)\n",
							padfTransform[0], padfTransform[3]);
			fprintf(stderr, "Pixel Size = (%.15f,%.15f)\n",
							padfTransform[1], padfTransform[5]);
		}
		else
			fprintf(stderr, "GeoTransform =\n  %.16g, %.16g, %.16g\n  %.16g, %.16g, %.16g\n",
							padfTransform[0], padfTransform[1], padfTransform[2],
							padfTransform[3], padfTransform[4], padfTransform[5]);
	}
	return;
}

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
	gds_t *gds)
{
	OGRSpatialReferenceH hSRS = OSRNewSpatialReference(NULL);
	OGRSpatialReferenceH hSrsSRS = OSRNewSpatialReference(NULL);
	double MinX, MinY;
	
	switch(gds->proj) {
		
		case GDS_LATLON:
		case GDS_GAUSSIAN_LATLON:
			OSRSetGeogCS(hSRS, "Sphere", NULL, "Sphere", gds->radius * 1000 , 0.0,
									 "Greenwich", 0.0, NULL, 0.0);
			gdal_set_projection(hDS, hSRS);
			if (gds->Lat2 < gds->Lat1) {
				MinX = gds->Lon2;
				MinY = gds->Lat2;
			}
			else {
				MinX = gds->Lon1;
				MinY = gds->Lat1;
			}
			set_geotransform(hDS, MinX, gds->Dx, 0.0,
											 MinY, gds->Dy, 0.0);
			break;
		
		case GDS_MERCATOR:
			OSRSetMercator(hSRS, gds->meshlat, gds->orientlon, gds->tan_Lat1, 0.0, 0.0);
			OSRSetGeogCS(hSRS, "Sphere", NULL, "Sphere", gds->radius * 1000 , 0.0,
									 "Greenwich", 0.0, NULL, 0.0);
			gdal_set_projection(hDS, hSRS);
			MinX = gds->Lon1;
			MinY = gds->Lat1;
			OSRSetWellKnownGeogCS(hSrsSRS, "WGS84");
			transform_origin(hSRS, hSrsSRS, &MinX, &MinY);
			set_geotransform(hDS, -(gds->Dx * (gds->Nx / 2)), gds->Dx, 0.0,
											 MinY- (gds->Dy * gds->Ny), gds->Dy, 0.0);
			break;
		
		case GDS_POLAR:
			OSRSetPS(hSRS, gds->meshlat, gds->orientlon, 1.0, 0.0, 0.0);
			OSRSetGeogCS(hSRS, "Sphere", NULL, "Sphere", gds->radius * 1000 , 0.0,
								"Greenwich", 0.0, NULL, 0.0);
			gdal_set_projection(hDS, hSRS);
			MinX = gds->Lon1;
			MinY = gds->Lat1;
			OSRSetWellKnownGeogCS(hSrsSRS, "WGS84");
			transform_origin(hSrsSRS, hSRS, &MinX, &MinY);
			set_geotransform(hDS, -(gds->Dx * (gds->Nx / 2)), gds->Dx, 0.0,
											 MinY, gds->Dy, 0.0);
			break;
		
		case GDS_LAMBERT:
			OSRSetLCC(hSRS, gds->tan_Lat1, gds->tan_Lat2, 0.0, gds->orientlon, 0.0, 0.0);
			//OSRSetLCC1SP(hSRS, gds->meshlat, gds->orientlon, 1.0, 0.0, 0.0);
			OSRSetGeogCS(hSRS, "Sphere", NULL, "Sphere", gds->radius * 1000 , 0.0,
								"Greenwich", 0.0, NULL, 0.0);
			gdal_set_projection(hDS, hSRS);
			MinX = gds->Lon1;
			MinY = gds->Lat1;
			OSRSetWellKnownGeogCS(hSrsSRS, "WGS84");
			transform_origin( hSrsSRS, hSRS, &MinX, &MinY);
			set_geotransform(hDS, -(gds->Dx * (gds->Nx / 2)), gds->Dx, 0.0,
											 MinY, gds->Dy, 0.0);
			break;
		
		case GDS_ORTHOGRAPHIC:
			OSRSetGeogCS(hSRS, "Sphere", NULL, "Sphere", gds->radius * 1000 , 0.0,
								"Greenwich", 0.0, NULL, 0.0);
			gdal_set_projection(hDS, hSRS);
			MinX = gds->Lon1;
			MinY = gds->Lat1;
			OSRSetWellKnownGeogCS(hSrsSRS, "WGS84");
			transform_origin( hSrsSRS, hSRS, &MinX, &MinY);
			set_geotransform(hDS, -(gds->Dx * (gds->Nx / 2)), gds->Dx, 0.0,
											 MinY- (gds->Dy * gds->Ny), gds->Dy, 0.0);
			break;
		
		case GDS_EQUATOR_EQUIDIST:
			OSRSetGeogCS(hSRS, "Sphere", NULL, "Sphere", gds->radius * 1000 , 0.0,
								"Greenwich", 0.0, NULL, 0.0);
			gdal_set_projection(hDS, hSRS);
			MinX = gds->Lon1;
			MinY = gds->Lat1;
			OSRSetWellKnownGeogCS(hSrsSRS, "WGS84");
			transform_origin( hSrsSRS, hSRS, &MinX, &MinY);
			set_geotransform(hDS, -(gds->Dx * (gds->Nx / 2)), gds->Dx, 0.0,
											 MinY- (gds->Dy * gds->Ny), gds->Dy, 0.0);
			break;
		
		case GDS_AZIMUTH_RANGE:
			OSRSetGeogCS(hSRS, "Sphere", NULL, "Sphere", gds->radius * 1000 , 0.0,
								"Greenwich", 0.0, NULL, 0.0);
			gdal_set_projection(hDS, hSRS);
			MinX = gds->Lon1;
			MinY = gds->Lat1;
			OSRSetWellKnownGeogCS(hSrsSRS, "WGS84");
			transform_origin( hSrsSRS, hSRS, &MinX, &MinY);
			set_geotransform(hDS, -(gds->Dx * (gds->Nx / 2)), gds->Dx, 0.0,
											 MinY- (gds->Dy * gds->Ny), gds->Dy, 0.0);
			break;
		
	}
	
	if (DEBUG) printf("minx=%g miny=%g\n", MinX, MinY);
	
	/***** cleanup *****/
	
	OSRDestroySpatialReference(hSrsSRS);
	
	return hSRS;
}

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
	int band_num)
{
	GDALRasterBandH band = NULL;
	
	if (!(band = GDALGetRasterBand(hDS, band_num))) {
		fprintf (stderr, "Band %d does not exist on dataset.\n", band_num);
		exit(EXIT_FAILURE);
	}
	
	return band;
}
