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
#include "ogrcode.h"


OGRLayerH contour (
	OGRSpatialReferenceH hSRS,
	OGRDataSourceH hDS,
	int interval,
	GDALRasterBandH hBand)
{

	/***** create the layer *****/
	
	OGRLayerH hLayer = create_layer(hDS, "contour", hSRS, wkbLineString);
	
	OGRFieldDefnH hFld = OGR_Fld_Create( "ID", OFTInteger);
	OGR_Fld_SetWidth(hFld, 8);
	OGR_L_CreateField(hLayer, hFld, FALSE);
	OGR_Fld_Destroy(hFld);
	
	/***** add the value field *****/
	
	hFld = OGR_Fld_Create("elev", OFTReal);
	OGR_Fld_SetWidth(hFld, 12);
	OGR_Fld_SetPrecision(hFld, 3);
	OGR_L_CreateField(hLayer, hFld, FALSE);
	OGR_Fld_Destroy(hFld);
	
	/***** contour *****/
	
	GDALContourGenerate(hBand, interval, 0.0, 0, NULL,
											FALSE, 0.0, hLayer, 0, 1, NULL, NULL);
	
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
	
  gds_t gds = {};
	
  GDALDatasetH hDS;
	
	/***** init *****/
	
  GDALAllRegister();
  OGRRegisterAll();
  
  /***** check args *****/
  
  if (argc < 5 || argc > 5) {
	fprintf(stderr, "USAGE: %s <grib file> <grib msg> <interval> <kml file>\n",
			argv[0]);
	exit(EXIT_FAILURE);
  }
  
  /***** open the grib file *****/
  
  fp = grib_open(argv[1], atoi(argv[2]), 'm');
  
  /***** read the grib raster into memory *****/
  
  raster = grib_read(fp, &gds);
  
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
	
	OGRDataSourceH hKmlDS = create_datasource(hKmlDriver, argv[4]);
	
	/***** check to see if we can go strait to kml *****/
	
	if (gds.proj == GDS_LATLON || gds.proj == GDS_GAUSSIAN_LATLON) {
		
		contour (hKmlSRS, hKmlDS, atof(argv[3]), hBand);
		
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
	
		OGRDataSourceH hMemDS = create_datasource(hMemDriver, argv[4]);
		
		/***** contour *****/
		
		OGRLayerH hMemLayer = contour (hMemSRS, hMemDS, atof(argv[3]), hBand);
		
		/***** create the layer to trasnslate too *****/
		
		OGRLayerH hKmlLayer = create_layer(hKmlDS, "contour", hKmlSRS, wkbLineString);
		
		OGRFieldDefnH hFld = OGR_Fld_Create( "ID", OFTInteger);
		OGR_Fld_SetWidth(hFld, 8);
		OGR_L_CreateField(hKmlLayer, hFld, FALSE);
		OGR_Fld_Destroy(hFld);
		
		/***** add the value field *****/
		
		hFld = OGR_Fld_Create("elev", OFTReal);
		OGR_Fld_SetWidth(hFld, 12);
		OGR_Fld_SetPrecision(hFld, 3);
		OGR_L_CreateField(hKmlLayer, hFld, FALSE);
		OGR_Fld_Destroy(hFld);
		
		/***** transform from mem to kml *****/
		
		transform(hMemSRS, hKmlSRS, hMemLayer, hKmlLayer);
		
		/***** cleanup *****/
		
		OGR_DS_Destroy(hMemDS);
	}

	/***** cleanup *****/
		

	OGR_DS_Destroy(hKmlDS);
		
	/***** cleaup raster stuff *****/
	
  return EXIT_SUCCESS;
}
