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
#include <gdal_alg.h>

#include "color.h"
#include "options.h"
#include "grib.h"
#include "buffer.h"
#include "color.h"
#include "ogrcode.h"
#include "gdalcode.h"
#include "contour.h"
#include "zipbuffer.h"
#include "kml.h"

void contour (
	GDALDatasetH hgdalDS,
	OGRSpatialReferenceH hSRS,
	OGRDataSourceH *hogrDS,
	OGRLayerH *hLayer,
	double interval,
	int id,
	int elev)
{
	/***** get the raster band *****/
	
	GDALRasterBandH hBand = get_band(hgdalDS, 1);
	
	/***** get the ogr driver *****/
	
	OGRSFDriverH hMemDriver = get_driver("Memory");
	
	/***** create the datasource *****/
	
	*hogrDS = create_datasource(hMemDriver, "hMemDS");
	
	/***** create the layer *****/
	
	*hLayer = create_layer(*hogrDS, "contour", hSRS, wkbLineString);
	
	/***** id field *****/
	
	create_field("ID", OFTInteger, 8, 0, *hLayer);
	
	/***** value field *****/
	
	create_field("elev", OFTReal, 12, 3, *hLayer);
	
	/***** contour *****/
	
	GDALContourGenerate(hBand, interval, 0.0, 0, NULL,
											FALSE, 0.0, *hLayer, id, elev, NULL, NULL);
	
	return;
}

void contour2kml(
	gds_t *gds,
	options *o,
	color_scale *cscales,
	OGRSpatialReferenceH hSRS,
	GDALRasterBandH hBand,
	OGRLayerH hLayer)
{
	buffer kmlbuf = {};
	color_scale *cscale;
	
	/***** kml header *****/
	
	kml_header(&kmlbuf);
	
	/***** kml linestyle *****/
	
	for (cscale = cscales ; *(cscale->color) ; cscale++) {
		kml_linestyle(&kmlbuf, cscale->color, cscale->color, "FF", 1);
	}
		
	/***** check to see if it needs transformed *****/
	
	if (gds->proj == GDS_LATLON || gds->proj == GDS_GAUSSIAN_LATLON) {
		ogr2kml(hLayer, &kmlbuf, cscales);
	}
	
	/***** translate first *****/
	else {
		
		/***** get the ogr driver *****/
		
		OGRSFDriverH hMemDriver = get_driver("Memory");
		
		/***** create the datasource *****/
		
		OGRDataSourceH hogrDS2 = create_datasource(hMemDriver, "hDS2");
		
		/***** set the spatial reference for kml *****/
	
		OGRSpatialReferenceH hSRS2 = OSRNewSpatialReference(NULL);
		OSRSetWellKnownGeogCS(hSRS2, "WGS84");
		
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
		
		OSRDestroySpatialReference(hSRS2);
		OGR_DS_Destroy(hogrDS2);
		
	}

	kml_footer(&kmlbuf);
		
	struct zip *kmz = zipbuffer_open(o->kmzfile);
	
	zipbuffer_add (o->kmlfile, kmz, &kmlbuf);
	
	zipbuffer_close(kmz);
	
	buffer_free(&kmlbuf);

	/***** cleanup *****/
		
//	OSRDestroySpatialReference(hSRS2);
	
}
