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
#include <wind.h>

#include "grib.h"
#include "gdalcode.h"
#include "ogrcode.h"

#include "error.h"

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

void transform(
	OGRSpatialReferenceH hMemSRS,
	OGRSpatialReferenceH hKmlSRS,
	OGRLayerH hMemLayer,
	OGRLayerH hKmlLayer)
{
	/***** Setup coordinate transformation *****/
	
	OGRCoordinateTransformationH *hTransform = 
		create_coord_transform(hMemSRS, hKmlSRS);
	
	/***** reset the source layer *****/
	
	OGR_L_ResetReading(hMemLayer);
	
	/***** loop while theres features *****/
	
	OGRFeatureH hSrcFeat;
	
	while((hSrcFeat = OGR_L_GetNextFeature(hMemLayer))) {
		
		CPLErrorReset();
		
		/***** make a new feature *****/
		
		OGRFeatureH hDstFeat = OGR_F_Create(OGR_L_GetLayerDefn(hKmlLayer));
		
		/***** translate feature *****/
		
		translate_feature(hDstFeat, hSrcFeat);
		
		
		/***** transform the feature if it translated *****/
		
		transform_feature(hDstFeat, hTransform);
		
		CPLErrorReset();
		
		/***** create the new feature in the layer *****/
		
		add_feature(hKmlLayer, hDstFeat);
		
		/***** cleanup *****/
		
		OGR_F_Destroy(hSrcFeat);
		OGR_F_Destroy(hDstFeat);
	}
	
	/***** cleanup *****/
	
	OCTDestroyCoordinateTransformation(hTransform);
	
	return;
}


int main(int argc, char **argv)
{
  FILE *fp = NULL;
  float *raster = NULL;
	
	float *Uraster = NULL;
	float *Vraster = NULL;
	int i;
	
  gds_t gds = {};
	
  GDALDatasetH hDS;
	
	/***** init *****/
	
	GDALAllRegister();
	OGRRegisterAll();
  
  /***** check args *****/
  
  if (argc < 6 || argc > 6) {
	fprintf(stderr, "USAGE: %s <grib file> <grib U msg> <grib V msg> <interval> <kml file>\n",
			argv[0]);
	exit(EXIT_FAILURE);
  }
  
  /***** open the grib file *****/
  
  fp = grib_open(argv[1], atof(argv[2]), 'e');
  
  /***** read the grib raster into memory *****/
  
  Uraster = grib_read(fp, &gds);
  
	/***** close the grib file *****/
	
	pclose(fp);
	
	/***** open the grib file *****/
  
  fp = grib_open(argv[1], atof(argv[3]), 'e');
  
  /***** read the grib raster into memory *****/
  
  Vraster = grib_read(fp, &gds);
  
	/***** close the grib file *****/
	
	pclose(fp);
	
	if (!(raster = malloc(sizeof(float) * gds.Npoints)))
		ERROR("main");
	
	for (i = 0; i < gds.Npoints ; i++) {
		raster[i] = uv2velocity(Uraster[i], Vraster[i]);
	}
	
	free(Uraster);
	free(Vraster);
	
	
	
	
  /***** open the raster in memory as a gdal data set *****/
  
  hDS = raster_open_mem(raster, gds.Nx, gds.Ny);
  
  /***** set the projection *****/
  
  OGRSpatialReferenceH hSrcSRS = set_projection(hDS, &gds);
  
	/***** get the raster band *****/
	
	GDALRasterBandH hBand = get_band(hDS, 1);
	
	/***** set the spatial reference for kml *****/
		
	OGRSpatialReferenceH hKmlSRS = OSRNewSpatialReference(NULL);
	OSRSetWellKnownGeogCS(hKmlSRS, "WGS84");
	
	/***** get the ogr driver *****/
	
	OGRSFDriverH hKmlDriver = get_driver("KML");
	
	/***** create the datasource *****/
	
	OGRDataSourceH hKmlDS = create_datasource(hKmlDriver, argv[5]);
	
	/***** check to see if we can go strait to kml *****/
	
	if (gds.proj == GDS_LATLON || gds.proj == GDS_GAUSSIAN_LATLON) {
		
		contour (hKmlSRS, hKmlDS, atof(argv[4]), hBand, 2, 3);
		
	}
	
	/***** ok not a simple lat lon raster *****/
	
	else {
		
		/***** set the spatial reference for mem *****/
		
		OGRSpatialReferenceH hMemSRS = hSrcSRS;
		char *wkt;
		
		OSRExportToWkt(hMemSRS, &wkt);
		//fprintf(stderr, "SrcWKT =\n%s\n\n", wkt);
		
		/***** get the ogr driver *****/
	
		OGRSFDriverH hMemDriver = get_driver("Memory");
	
		/***** create the datasource *****/
	
		OGRDataSourceH hMemDS = create_datasource(hMemDriver, argv[5]);
		
		/***** contour *****/
		
		OGRLayerH hMemLayer = contour (hMemSRS, hMemDS, atof(argv[4]), hBand, 0, 1);
		
		/***** create the layer to trasnslate too *****/
		
		OGRLayerH hKmlLayer = create_layer(hKmlDS, "contour", hKmlSRS, wkbLineString);
		
			/***** id field *****/
	
		create_field("ID", OFTInteger, 8, 0, hKmlLayer);
		
		/***** value field *****/
		
		create_field("elev", OFTReal, 12, 3, hKmlLayer);

		/***** transform from mem to kml *****/
		
		transform(hMemSRS, hKmlSRS, hMemLayer, hKmlLayer);
		
		/***** cleanup *****/
		
		OGR_DS_Destroy(hMemDS);
	}

	/***** cleanup *****/
		
	OSRDestroySpatialReference(hSrcSRS);
	OSRDestroySpatialReference(hKmlSRS);
	
	OGR_DS_Destroy(hKmlDS);
	
	OGRCleanupAll();
	/***** cleaup raster stuff *****/
	
	GDALClose(hDS);
	
	free(raster);
	GDALDestroyDriverManager();
	
  return EXIT_SUCCESS;
}
