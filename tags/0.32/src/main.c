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
#include "gribdump.h"
#include <libkml/libKML.h>
#include "color.h"
#include "ogrcode.h"
#include "gdalcode.h"
#include "contour.h"
#include "merge.h"
#include "style.h"

#define DEBUG 1


int main(int argc, char **argv)
{
	options o = {};
	
	float *raster[100] = {};
	gds_t gds[100] = {};
	
	GDALDatasetH hDS[100] = {};
	GDALRasterBandH hBand[100] = {};
	OGRSpatialReferenceH hSRS[100] = {};
	
	GDALDatasetH t_hDS = NULL;
	GDALRasterBandH t_hBand;
	OGRSpatialReferenceH t_hSRS = NULL;
	
	color_scale *cscales;
	OGRDataSourceH hogrDS;
	OGRLayerH hLayer;
	int i;
	
	/***** init *****/
	
	fprintf(stderr, "doing init\n");
	GDALAllRegister();
	OGRRegisterAll();
	
	/***** check args *****/
	
	fprintf(stderr, "get_options\n");
	get_options(argc, argv, &o);
	
	/***** get the raster(s) *****/
	
	if (!o.quasi) {
		if (o.wind) {
			for (i = 0; i < o.count ; i++) {
				fprintf(stderr, "do_wind_grib\n");
				raster[i] = do_wind_grib(&o, o.ugribfile[i], o.vgribfile[i],
																 o.ugribmsg[i], o.vgribmsg[i], gds + i);
			}
		}
		else if (o.and) {
			for (i = 0; i < o.count ; i++) {
				fprintf(stderr, "do_and_grib\n");
				raster[i] = do_and_grib(&o, o.ugribfile[i], o.vgribfile[i],
																o.ugribmsg[i], o.vgribmsg[i], gds + i);
			}
		}
		else if (o.diff) {
			for (i = 0; i < o.count ; i++) {
				fprintf(stderr, "do_diff_grib\n");
				raster[i] = do_diff_grib(&o, o.ugribfile[i], o.vgribfile[i],
																o.ugribmsg[i], o.vgribmsg[i], gds + i);
			}
		}
		else {
			for (i = 0; i < o.count ; i++) {
				fprintf(stderr, "do_grib\n");
				raster[i] = do_grib(&o, o.gribfile[i], o.gribmsg[i], gds + i);
			}
		}
	}
	
	else {
		if (o.wind) {
			for (i = 0; i < o.count ; i++) {
				fprintf(stderr, "do_wind_grib\n");
				raster[i] = do_wind_gribdump(&o, o.ugribfile[i], o.vgribfile[i],
																 o.ugribmsg[i], o.vgribmsg[i], o.quasi, gds + i);
			}
		}
		else if (o.and) {
			for (i = 0; i < o.count ; i++) {
				fprintf(stderr, "do_and_grib\n");
				raster[i] = do_and_gribdump(&o, o.ugribfile[i], o.vgribfile[i],
																o.ugribmsg[i], o.vgribmsg[i], o.quasi, gds + i);
			}
		}
		else if (o.diff) {
			for (i = 0; i < o.count ; i++) {
				fprintf(stderr, "do_diff_grib\n");
				raster[i] = do_diff_gribdump(&o, o.ugribfile[i], o.vgribfile[i],
																o.ugribmsg[i], o.vgribmsg[i], o.quasi, gds + i);
			}
		}
		else {
			for (i = 0; i < o.count ; i++) {
				fprintf(stderr, "do_grib\n");
				raster[i] = do_gribdump(&o, o.gribfile[i], o.gribmsg[i], o.quasi, gds + i);
			}
		}
	}
	
	/***** get the color scale *****/
	
	fprintf(stderr, "color_getscale\n");
	cscales = color_getscale(&o);
	
	/***** convert to gdal dataset(s) *****/
	
	for (i = 0; i < o.count ; i++) {
		fprintf(stderr, "do_gdal\n");
		hDS[i] = do_gdal(raster[i], gds + i, hSRS + i, hBand + i);
	}
	
	/***** merge data? *****/
	
	if (o.count > 1) {
		t_hDS = merge(hDS, gds->missing, gds->missing_value);
		t_hBand = GDALGetRasterBand(t_hDS, 1);
		t_hSRS = OSRNewSpatialReference(GDALGetProjectionRef(t_hDS));
		//t_hSRS = *hSRS;
	}
	
	/***** nope *****/
	
	else {
		t_hDS = *hDS;
		t_hSRS = *hSRS;
		t_hBand = *hBand;
	}
		
	if (o.tiffile) {
		char *ccopt[] = {
			"TILED=YES",
			NULL
		};
		fprintf(stderr, "createcopy\n");
		GDALDatasetH tiff = GDALCreateCopy(GDALGetDriverByName("gtiff"),
																			 o.tiffile,
																			 t_hDS,
																			 0, /*bStrict*/
																			 ccopt,
																			 GDALTermProgress,
																			 NULL);
		GDALClose(tiff);
		
	}
		
	if (o.kmlfile) {
		
		/***** make a linestring *****/
		
		fprintf(stderr, "contour\n");
		contour (t_hDS, t_hSRS, &hogrDS, &hLayer, &o, 0, 1, gds, cscales);
		
		/***** output to kml *****/
		
		fprintf(stderr, "contour2kml\n");
		contour2kml(gds, &o, cscales, t_hSRS, hogrDS, hLayer);
		
		OGR_DS_Destroy(hogrDS);
		
		OGRCleanupAll();
	}
	
	free(cscales);
	
	/***** cleaup raster stuff *****/
	
	if (o.count) {
		for (i = 0; i < o.count ; i++) {
			OSRDestroySpatialReference(hSRS[i]);
			GDALClose(hDS[i]);
			free(raster[i]);
		}
	}
	else {
		OSRDestroySpatialReference(*hSRS);
		GDALClose(*hDS);
		free(*raster);
	}
	
	GDALDestroyDriverManager();
	
	return EXIT_SUCCESS;
}
