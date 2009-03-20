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

#include <gdal_alg.h>

#include "grib.h"
#include "gdalcode.h"
#include "buffer.h"
#include "ogrcode.h"
#include "color.h"
#include "zipbuffer.h"
#include "kml.h"


void ogr2kml(
	OGRLayerH hLayer,
	buffer *kmlbuf,
	color_scale *cscales)
{
	OGRFeatureH hFeat;
	double value;
	buffer coordbuf = {};
	
					
	OGR_L_ResetReading(hLayer);

	/***** loop while theres features *****/
			
	while((hFeat = OGR_L_GetNextFeature(hLayer))) {
	
		CPLErrorReset();
		
		/***** the second field contains the data value *****/
		
		value = OGR_F_GetFieldAsDouble(hFeat, 1);
		
		/***** kml placemark header *****/
		
		kml_placemark_header(kmlbuf, NULL, NULL, color_checkscale(cscales, value));
		
		/***** reset the points buffer *****/
		
		kml_linestring_header(kmlbuf, 0, 0);
		
		getpoints(hFeat, kmlbuf);
		
		kml_linestring_footer(kmlbuf);
		kml_placemark_footer(kmlbuf);
		OGR_F_Destroy(hFeat);
	}
	
	buffer_free(&coordbuf);
	
	return;
}
	

OGRLayerH contour (
	OGRSpatialReferenceH hSRS,
	OGRDataSourceH hDS,
	double interval,
	GDALRasterBandH hBand,
	int id,
	int elev)
{

	/***** create the layer *****/
	
	OGRLayerH hLayer = create_layer(hDS, "contour", hSRS, wkbLineString);
	
	/***** id field *****/
	
	create_field("ID", OFTInteger, 8, 0, hLayer);
	
	/***** value field *****/
	
	create_field("elev", OFTReal, 12, 3, hLayer);
	
	/***** contour *****/
	
	GDALContourGenerate(hBand, interval, 0.0, 0, NULL,
											FALSE, 0.0, hLayer, id, elev, NULL, NULL);
	
	return hLayer;
}


	
float *do_grib(
	char *gribfile,
	int msg,
	gds_t *gds)
{
	FILE *fp = NULL;
	float *raster;
	
  /***** open the grib file *****/
  
  fp = grib_open(gribfile, msg, 'm');
  
  /***** read the grib raster into memory *****/
  
  raster = grib_read(fp, gds);
  
	/***** close the grib file *****/
	
	pclose(fp);
	
	return raster;
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

int main(int argc, char **argv)
{
  
  float *raster = NULL;
	gds_t gds = {};
	GDALDatasetH hDS;
	GDALRasterBandH hBand;
	OGRSpatialReferenceH hSRS;
	color_scale *cscales;
	color_scale *cscale;
	buffer kmlbuf = {};
	
	/***** init *****/
	
	GDALAllRegister();
	OGRRegisterAll();
  
  /***** check args *****/
  
  if (argc < 7 || argc > 7) {
	fprintf(stderr, "USAGE: %s <grib file> <grib msg> <interval> <color scale> <kml file> <kmz file>\n",
			argv[0]);
	exit(EXIT_FAILURE);
  }
  
	raster = do_grib(argv[1], atoi(argv[2]), &gds);
	
	hDS = do_gdal(raster, &gds, &hSRS, &hBand);
  
	
	/***** set the spatial reference for kml *****/
		
	OGRSpatialReferenceH hSRS2 = OSRNewSpatialReference(NULL);
	OSRSetWellKnownGeogCS(hSRS2, "WGS84");
	
	/***** get the ogr driver *****/
	
	OGRSFDriverH hMemDriver = get_driver("Memory");
	
	/***** create the datasource *****/
	
	OGRDataSourceH hogrDS = create_datasource(hMemDriver, "hMemDS");
		
	/***** contour *****/
		
	OGRLayerH hLayer = contour (hSRS, hogrDS, atof(argv[3]), hBand, 0, 1);
	
	/***** kml header *****/
	
	kml_header(&kmlbuf);
	
	/***** get the color scale *****/
	
	cscales = color_getscale(argv[4]);
	
	/***** kml linestyle *****/
	
	for (cscale = cscales ; *(cscale->color) ; cscale++) {
		kml_linestyle(&kmlbuf, cscale->color, cscale->color, "FF", 1);
	}
		
	/***** check to see if it needs transformed *****/
	
	if (gds.proj == GDS_LATLON || gds.proj == GDS_GAUSSIAN_LATLON) {
		ogr2kml(hLayer, &kmlbuf, cscales);
	}
	
	/***** translate first *****/
	else {
		
		/***** create the datasource *****/
		
		OGRDataSourceH hogrDS2 = create_datasource(hMemDriver, "hDS2");
		
		/***** create the layer to trasnslate too *****/
		
		OGRLayerH hLayer2 = create_layer(hogrDS2, "contour", hSRS2, wkbLineString);
		
		/***** id field *****/
	
		create_field("ID", OFTInteger, 8, 0, hLayer2);
		
		/***** value field *****/
		
		create_field("elev", OFTReal, 12, 3, hLayer2);
		
		/***** transform *****/
		
		transform(hSRS, hLayer, hSRS2, hLayer2);
		
		ogr2kml(hLayer2, &kmlbuf, cscales);
		
		/***** cleanup *****/
		
		OGR_DS_Destroy(hogrDS2);
	}

	kml_footer(&kmlbuf);
	
	struct zip *kmz = zipbuffer_open(argv[6]);
	
	zipbuffer_add (argv[5], kmz, &kmlbuf);
	
	zipbuffer_close(kmz);
	
	buffer_free(&kmlbuf);

	/***** cleanup *****/
		
	OSRDestroySpatialReference(hSRS);
	OSRDestroySpatialReference(hSRS2);
	
	OGR_DS_Destroy(hogrDS);
	
	OGRCleanupAll();
	/***** cleaup raster stuff *****/
	
	GDALClose(hDS);
	
	free(raster);
	GDALDestroyDriverManager();
	
  return EXIT_SUCCESS;
}
