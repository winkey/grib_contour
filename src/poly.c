/***************************************************************************
 *            poly.c
 *
 *  Mon Jan 19 09:41:07 2009
 *  Copyright  2009  rush
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
#include <gdal_alg.h>

#include "options.h"
#include "color.h"
#include "grib.h"
#include "color.h"
#include "ogrcode.h"
#include "gdalcode.h"
#include "poly.h"
#include "error.h"

void poly (
	GDALDatasetH hgdalDS,
	OGRSpatialReferenceH hSRS,
	OGRDataSourceH hogrDS,
	OGRLayerH *hLayer,
	options *o,
	int id,
	int elev,
	gds_t *gds,
	color_scale *cscales)
{
	/***** get the raster band *****/
	
	GDALRasterBandH hBand = get_band(hgdalDS, 1);
	
	/***** create the layer *****/
	
	*hLayer = create_layer(hogrDS, "poly", hSRS, wkbPolygon);
	
	/***** id field *****/
	
	create_field("ID", OFTInteger, 8, 0, *hLayer);
	
	/***** value field *****/
	
	create_field("elev", OFTReal, 12, 3, *hLayer);
	
	/***** polygonize *****/
	
	GDALPolygonize(hBand, NULL, *hLayer, 1, NULL, NULL, NULL);

	
	return;
}

#include <stdio.h>
#include <stdlib.h>

#include <cpl_conv.h>
#include <ogr_api.h>
#include <ogr_srs_api.h>

#include <libDataStruct/DLList.h>
#include <libDataStruct/MWTree.h>

#include "options.h"
#include "color.h"
#include "grib.h"

#include "ogrcode.h"
#include "error.h"

#define DEBUG 1

/*******************************************************************************
	MWTree function to cmp 2 linestrings for contains
*******************************************************************************/

int polysort_tree_cmp_linestring(
	void *d1,
	void *d2)
{
	int result = 0;
	
	OGRGeometryH hGeomPoly1 = d1;
	OGRGeometryH hGeomPoly2 = d2;
		
	if (OGR_G_Contains(hGeomPoly1, hGeomPoly2))
		result = 1;
	else if (OGR_G_Contains(hGeomPoly2, hGeomPoly1))
		result = -1;
	else
		result = 0;
	
	printf("polysort_tree_cmp_linestring result = %i\n", result);
	
	return result;
}

/*******************************************************************************
	traverse function to iterate the tree and add the polys as outer and inner rings
********************************************************************************/

void * polysort_tree_traverse_rings(
	MWTree *t,
	MWTree_node *n,
	void *data,
	void *extra)
{
	OGRGeometryH hGeom = data;
	OGRLayerH hLayer = extra;
	
	/***** go though the nodes children they are interior rings *****/
  
	int j = 1;
	DLList_node *c;
	for (c = n->children.head ; c ; c = c->next, j++) {
		MWTree_node *cnode = c->data;
		OGRGeometryH hGeomC = cnode->data;
		
		int i;
		for (i = 0 ; i < OGR_G_GetGeometryCount(hGeomC) ; i++) {
			OGRGeometryH hGeomSub = OGR_G_GetGeometryRef(hGeomC, i);
			
			if (hGeomSub) {
				if (OGRERR_NONE != OGR_G_AddGeometry(hGeom, hGeomSub))
					ERROR("polysort_tree_traverse_rings");
			}
		}
	}
	
	/***** add to the layer *****/
	if (!hGeom)
		printf("polysort_tree_traverse_rings hGeom null\n");
		
	OGRFeatureH hFeat = OGR_F_Create (OGR_L_GetLayerDefn(hLayer));
	OGR_F_SetGeometryDirectly(hFeat, hGeom);
	OGR_L_CreateFeature (hLayer, hFeat);
	
	
	return NULL;
}
		
		
	
	

/*******************************************************************************
	function to create a polygon from a layers extent
*******************************************************************************/

OGRGeometryH polysort_extent2poly(
	OGRLayerH hLayer)
{
	OGREnvelope psExtent;
	OGRGeometryH hGeomRing;
	OGRGeometryH hGeomPoly;
	
	if (OGRERR_NONE != OGR_L_GetExtent(hLayer, &psExtent, 1))
		ERROR("extent2poly OGR_L_GetExtent");

	if (!(hGeomRing = OGR_G_CreateGeometry(wkbLinearRing)))
		ERROR("extent2poly OGR_G_CreateGeometry");
	
	OGR_G_AddPoint(hGeomRing, psExtent.MinX, psExtent.MinY, 0);
	OGR_G_AddPoint(hGeomRing, psExtent.MinX, psExtent.MaxY, 0);
	OGR_G_AddPoint(hGeomRing, psExtent.MaxX, psExtent.MaxY, 0);
	OGR_G_AddPoint(hGeomRing, psExtent.MaxX, psExtent.MinY, 0);
	OGR_G_AddPoint(hGeomRing, psExtent.MinX, psExtent.MinY, 0);
	
	if (!(hGeomPoly = OGR_G_CreateGeometry(wkbPolygon)))
		ERROR("extent2poly OGR_G_CreateGeometry");
	
	if (OGRERR_NONE != OGR_G_AddGeometry(hGeomPoly, hGeomRing))
		ERROR("extent2poly OGR_G_AddGeometry");
	
	return hGeomPoly;
}

/*******************************************************************************
function to create a convert a polygon layer into sorted polygons with inner and outer rings
*******************************************************************************/

OGRLayerH polysort (
	OGRSpatialReferenceH hSRS,
	OGRDataSourceH hogrDS,
	OGRLayerH hLayer)
{
	DLList open = {};
	
	MWTree tree = {};
	tree.cmp = polysort_tree_cmp_linestring;
	
	OGRGeometryH hGeom = NULL;
	
	/***** create the polygon layer *****/
	
	OGRLayerH hPolyLayer;
	if (!(hPolyLayer = OGR_DS_CreateLayer(hogrDS, "polygon", hSRS, wkbPolygon, NULL)))
		ERROR("c2p OGR_DS_CreateLayer");
	
	/***** set the outer ring as the datasets extent *****/
	
	
	OGRGeometryH hGeomPoly = polysort_extent2poly(hLayer);
	
	if (!MWTree_insert(&tree, hGeomPoly))
		ERROR("c2p MWTree_insert");
	
	/***** loop while theres features *****/
	
	OGR_L_ResetReading(hLayer);
	OGRFeatureH hFeat;
	while((hFeat = OGR_L_GetNextFeature(hLayer))) {
		CPLErrorReset();
		hGeom = OGR_F_GetGeometryRef(hFeat);
		double elev = OGR_F_GetFieldAsDouble(hFeat, 1);
		
		OGRGeometryH hGeomRing = OGR_G_GetGeometryRef(hGeom, 0);

    /***** add it to the tree if its a ring *****/
    
		if (OGR_G_IsRing(hGeom)) {
			if (!MWTree_insert(&tree, hGeom))
				ERROR("c2p MWTree_insert");
		}

    /****** if its not a ring see if its simple to make it one *****/
    
    else {
      int nPoints = OGR_G_GetPointCount(hGeom);
      double x1, x2, y1, y2, z1, z2;

      OGR_G_GetPoint(hGeom, 0, &x1, &y1, &z1);
      OGR_G_GetPoint(hGeom, nPoints - 1, &x2, &y2, &z2);

      if (x1 == x2 || y1 == y2) {
        OGR_G_SetPoint(hGeom, nPoints, x1, y1, z1);

        if (!MWTree_insert(&tree, hGeom))
				  ERROR("c2p MWTree_insert");
      }
    }
    
      
	}
	
	/***** fill our new poly layer ****/
	
	MWTree_levelorder(&tree, 0, polysort_tree_traverse_rings, hPolyLayer);
	
	return hPolyLayer;
}

