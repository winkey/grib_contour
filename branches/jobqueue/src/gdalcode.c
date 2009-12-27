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

#include "options.h"
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
	
	if (!raster || !width || !height)
		ERROR("raster_open\n 0 length raster");
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
	//if (DEBUG) fprintf (stderr, "%s\n", wkt);
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
	double MinX, MinY, MaxX, MaxY;
	
	switch(gds->proj) {
		
		case GDS_LATLON:
		case GDS_GAUSSIAN_LATLON:
		  OSRSetWellKnownGeogCS(hSRS, "WGS84");
			//OSRSetGeogCS(hSRS, "Sphere", NULL, "Sphere", gds->radius * 1000 , 0.0,
			//						 "Greenwich", 0.0, NULL, 0.0);
			gdal_set_projection(hDS, hSRS);
			
			/***** check right lon *****/
			
			if (gds->Lon1 == 180 && gds->Lon2 < 0 && gds->Lon1 + gds->Dy * gds->Ny != gds->Lon2)
				gds->Lon1 *= -1;
		
				
			/***** is the pixel size correct? *****/
		/*
			
			if (MAX(gds->Lat1, gds->Lat2) / MIN(gds->Lat1, gds->Lat2) - gds->Dy > .00001) {
					
				if (gds->Lon1 == 180.000000 && gds->Lon2 < 0)
					gds->Lon1 *= -1;
				
				double Lat1 = MIN(gds->Lat1, gds->Lat2);
				double Lat2 = MAX(gds->Lat1, gds->Lat2);
				double Lon1 = MIN(gds->Lon1, gds->Lon2);
				double Lon2 = MAX(gds->Lon1, gds->Lon2);
				
				gds->Dy = (Lat2 - Lat1) / gds->Ny;
				gds->Dx = (Lon2 - Lon1) / gds->Nx;
				printf("gds->Lat1, %f, gds->Lat2 %f\n", gds->Lat1, gds->Lat2);
				printf("Lat1, %f, Lat2 %f\n", Lat1, Lat2);
				printf("gds->Lon1, %f, gds->Lon2 %f\n", gds->Lon1, gds->Lon2);
				printf("Lon1, %f, Lon2 %f\n", Lat1, Lat2);
				printf("gds->Dx %f, gds->Dy %f\n", gds->Dx, gds->Dy);
				
				
			}
			*/
			/***** is it center of pixel? *****/
		
#warning fixme
			if ((int)(gds->Lat1 * 100) % 100 && 0) {
				printf("correcting center of p[ixel issue\n");
				gds->Lat1 += gds->Dy / 2.0;
				gds->Lon1 -= gds->Dx / 2.0;
				gds->Lat2 -= gds->Dy / 2.0;
				gds->Lon2 += gds->Dx / 2.0;
				
				gds->Dy = (gds->Lat1 - gds->Lat2) / gds->Ny;
				gds->Dx = (gds->Lon1 + gds->Lon2) / gds->Nx;
			
				MinY = MIN(gds->Lat2, gds->Lat1);
				MinX = MIN(gds->Lon2, gds->Lon1);
				
				MinX += gds->Dx / 2.0;
				MinY += gds->Dy / 2.0;

			}
			
			else {
				MinY = MIN(gds->Lat2, gds->Lat1);
				//MinX = MIN(gds->Lon2, gds->Lon1);
				//MinY = gds->Lat1;
				MinX = gds->Lon1;
			}
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
			break;
		
	}

	set_geotransform(hDS, MinX, gds->Dx, 0.0,
									      MinY, gds->Dy, 0.0);
	
	if (DEBUG) {
		printf("minx=%g miny=%g\n", MinX, MinY);
	}
	
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

GDALDatasetH do_gdal(
	float *raster,
	gds_t *gds,
	OGRSpatialReferenceH *hSrcSRS,
	GDALRasterBandH *hBand)
{
	
	/***** open the raster in memory as a gdal data set *****/
  
  GDALDatasetH hDS = raster_open_mem(raster, gds->Nx, gds->Ny);
  
  /***** set the projection *****/
  
  *hSrcSRS = set_projection(hDS, gds);
  
	/***** get the raster band *****/
	
	*hBand = get_band(hDS, 1);
	
	return hDS;
}

/*******************************************************************************
	function to get a gdal driver by its name
	
	args:
						name			the name of the driver
	
	returns:
						the gdal driver
*******************************************************************************/

GDALDriverH gdal_get_driver_by_name (
	char *name)
{
	GDALDriverH hDriver;
	
	if(!(hDriver = GDALGetDriverByName(name)))
		ERROR("gdal_get_driver_by_name");
	
	return hDriver;
}


/*******************************************************************************
	function to create a new gdal dataset
	
	args:
						hDriver			the gdal driver
						filename		the file to create
						xsize				the width of the raster
						ysize				the height of the raster
	
	returns:
						the gdal driver
*******************************************************************************/
/*
GDALDatasetH gdal_create(
	GDALDriverH hDriver,
	char *filename,
	int xsize,
	int ysize,
		GDALDataType  	eBandType,
		char **  	papszOptions
												 
												 
    GDALDatasetH hDstDS;        
    char **papszOptions = NULL;

    hDstDS = GDALCreate( hDriver, filename, xsize, ysize, 3, GDT_Byte, 
                         papszOptions );
*/
