/***************************************************************************
 *            main.c
 *
 *  Wed Jan 16 11:25:01 2008
 *  Copyright  2008  winkey
 *  <rush@winkey.org>
 ****************************************************************************/

/*
 * main.c
 * Copyright (C) winkey 2008 <rush@winkey.org>
 * 
 * main.c is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * main.c is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>


#include "options.h"
#include "grib.h"
#include <libkml/libKML.h>
#include "color.h"
#include "ogrcode.h"
#include "gdalcode.h"
#include "contour.h"





int main(int argc, char **argv)
{
  options o = {};
	
  float *raster = NULL;
	gds_t gds = {};
	GDALDatasetH hDS;
	GDALRasterBandH hBand;
	OGRSpatialReferenceH hSRS;
	color_scale *cscales;
	OGRDataSourceH hogrDS;
	OGRLayerH hLayer;
	
	/***** init *****/
	
	GDALAllRegister();
	OGRRegisterAll();
  
  /***** check args *****/
  
	get_options(argc, argv, &o);
  
	/***** get the raster *****/
	
	if (o.wind)
		raster = do_wind_grib(&o, &gds);
	else
		raster = do_grib(&o, &gds);
	
	/***** get the color scale *****/
	
	cscales = color_getscale(o.scalename);
	
	
	hDS = do_gdal(raster, &gds, &hSRS, &hBand);
  
	if (o.tiffile) {
		
		/***** make an image *****/
		
	}
	
	if (o.kmlfile) {
		
		/***** make a linestring *****/
		
		contour (hDS, hSRS, &hogrDS, &hLayer, o.interval, 0, 1);
		
		
		contour2kml(&gds, &o, cscales, hSRS, hBand, hLayer);
		
		OSRDestroySpatialReference(hSRS);
		
		OGR_DS_Destroy(hogrDS);
	
		OGRCleanupAll();
		}
	
	free(cscales);
	
	/***** cleaup raster stuff *****/
	
	GDALClose(hDS);
	
	free(raster);
	GDALDestroyDriverManager();
	
  return EXIT_SUCCESS;
}
