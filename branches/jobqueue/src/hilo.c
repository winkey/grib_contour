/***************************************************************************
 *            hilo.c
 *
 *  Mon Aug 17 21:40:02 2009
 *  Copyright  2009  Brian Case
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
#include <libKML/libKML.h>
#include <libogr2kml/libogr2kml.h>
#include <libDataStruct/DLList.h>
#include <libDataStruct/MWTree.h>

#include "options.h"
#include "color.h"
#include "grib.h"
#include "color.h"
#include "ogrcode.h"
#include "gdalcode.h"
#include "hilo.h"
#include "style.h"
#include "error.h"

#define DEBUG 1

typedef struct {
	OGRFeatureH hFeat;
	OGRGeometryH hGeom;
} hilo_data;


int hilocmp (
	void *data1,
	void *data2)
{
	int result = 0;

	OGRGeometryH hGeom1 = OGR_F_GetGeometryRef(data1);
	OGRGeometryH hGeom2 = OGR_F_GetGeometryRef(data2);


	if (!OGR_G_IsRing (hGeom1))
		return 0;
	if (!OGR_G_IsRing (hGeom2))
    return 0;
  /***** turn them into polys *****/

	OGRGeometryH poly1 = OGR_G_CreateGeometry(wkbPolygon);
	OGRGeometryH hGeomlr1 = OGR_G_CreateGeometry(wkbLinearRing);

	int i;
	for (i = 0; i < OGR_G_GetPointCount(hGeom1); i++) {
		double x, y, z;
		OGR_G_GetPoint (hGeom1, i, &x, &y, &z);
		OGR_G_SetPoint (hGeomlr1, i, x, y, z);
	}

	OGR_G_AddGeometryDirectly(poly1, hGeomlr1);
			
	OGRGeometryH poly2 = OGR_G_CreateGeometry(wkbPolygon);
	OGRGeometryH hGeomlr2 = OGR_G_CreateGeometry(wkbLinearRing);

	for (i = 0; i < OGR_G_GetPointCount(hGeom2); i++) {
		double x, y, z;
		OGR_G_GetPoint (hGeom2, i, &x, &y, &z);
		OGR_G_SetPoint (hGeomlr2, i, x, y, z);
	}

	OGR_G_AddGeometryDirectly(poly2, hGeomlr2);

	/***** contains not contains *****/
	
	if (OGR_G_Contains( poly1,poly2))
		result = 1;
	else if (OGR_G_Contains( poly2,poly1))
		result = -1;

	OGR_G_DestroyGeometry(poly1);
	OGR_G_DestroyGeometry(poly2);
	
	return result;
}

void hilofree(void *data) {
  OGR_F_Destroy(data);
}

void *hilo_traverse(MWTree *t, MWTree_node *node, void *data, void *extra)
{
	
	if (node->parent && // not the root
	    !node->children.head && // no children
	    node->parent->children.length == 1 // no siblings
	   ) {

		OGRLayerH hLayer = extra;

		/***** get the features geometry *****/
		
		OGRFeatureH hFeat = data;
		OGRGeometryH hGeom = OGR_F_GetGeometryRef(hFeat);

		/***** find the center of the geometry *****/
		
		OGREnvelope hEnv;
		OGR_G_GetEnvelope(hGeom, &hEnv);

		/****** create a new point geometry *****/
			
		OGRGeometryH hGeomNew = OGR_G_CreateGeometry(wkbPoint);

		/***** add the center point to the new point geometry *****/
		
		OGR_G_AddPoint_2D(hGeomNew, (hEnv.MinX + hEnv.MaxX) * .5, (hEnv.MinY + hEnv.MaxY) * .5);
		
		/***** get the layer def *****/
		
		OGRFeatureDefnH hLayerDef = OGR_L_GetLayerDefn(hLayer);
		
		/***** create a new feature *****/
		
		OGRFeatureH hFeatNew = OGR_F_Create (hLayerDef);
		
		/***** add the point to the feature *****/

		OGR_F_SetGeometryDirectly(hFeatNew, hGeomNew);

		/***** set the features name *****/

		OGRFeatureDefnH hFD = OGR_F_GetDefnRef(hFeat);
		int elevidx = OGR_FD_GetFieldIndex(hFD, "elev");		 

		double value = OGR_F_GetFieldAsDouble(hFeat, elevidx);
		
		int nameidx = OGR_FD_GetFieldIndex(hLayerDef, "name");
		char name[100];
		snprintf(name, sizeof(name), "%.1lf", value);
		OGR_F_SetFieldString (hFeatNew, nameidx, name);

		/***** get the parents info *****/

		OGRFeatureH hFeatParent = node->parent->data;
		double valueparent = OGR_F_GetFieldAsDouble(hFeatParent, elevidx);
		
		/***** set the features stylestring *****/

		if (value < valueparent)
			OGR_F_SetStyleString(hFeatNew, "@lo");
		else
			OGR_F_SetStyleString(hFeatNew, "@hi");
		
		/***** add the feature to a layer *****/
		
		OGR_L_CreateFeature (hLayer, hFeatNew);

		/***** cleanup *****/

		OGR_F_Destroy(hFeatNew);
		
	}

	return NULL;
}


void hilo(
	OGRDataSourceH hDS,
	OGRLayerH hLayer,
  OGRSpatialReferenceH hSRS)
{


  
	MWTree t = {};

	t.cmp = hilocmp;
	t.free = hilofree;

  if (DEBUG)
    fprintf(stderr, "hilo\n");
  
	/***** get the extent of the layer *****/
	
	OGREnvelope hEnv;
	OGR_L_GetExtent(hLayer, &hEnv, 1);

	/***** turn the extent to a geom *****/

	OGRGeometryH hGeom = OGR_G_CreateGeometry(wkbLineString);
	
	OGR_G_AddPoint_2D(hGeom, hEnv.MinX, hEnv.MinY);
	OGR_G_AddPoint_2D(hGeom, hEnv.MinX, hEnv.MaxY);
	OGR_G_AddPoint_2D(hGeom, hEnv.MaxX, hEnv.MaxY);
	OGR_G_AddPoint_2D(hGeom, hEnv.MaxX, hEnv.MinY);
	OGR_G_AddPoint_2D(hGeom, hEnv.MinX, hEnv.MinY);

	OGRFeatureH hFeatEnv;
	hFeatEnv = OGR_F_Create(OGR_L_GetLayerDefn(hLayer));
	
	/***** add the point to the feature *****/

	OGR_F_SetGeometryDirectly(hFeatEnv, hGeom);
	MWTree_insert (&t, hFeatEnv);
	
	/***** stuff all the contours in an mway tree *****/

	OGR_L_ResetReading(hLayer);
	OGRFeatureH hFeat;
	
	while((hFeat = OGR_L_GetNextFeature(hLayer))) {
		if (OGR_F_GetGeometryRef(hFeat))
			MWTree_insert (&t, hFeat);
	}

	/***** create the new hilo layer *****/
	
	OGRLayerH hLayernew	= OGR_DS_CreateLayer (hDS, "HiLo", hSRS, wkbPoint, NULL);

	OGRFieldDefnH hField = OGR_Fld_Create("name", OFTString);
	OGR_L_CreateField(hLayernew, hField, FALSE);
	OGR_Fld_Destroy(hField);
	
	/***** parse the tree levelorder *****/

	MWTree_levelorder (&t, 0, hilo_traverse, hLayernew);

	/***** add the style table *****/

	/***** set the style table *****/
		
	OGRStyleTableH hSTBL = OGR_STBL_Create();
	OGRStyleMgrH hSM = OGR_SM_Create(hSTBL);
		
	/***** clear the current style in the manager *****/
			
	OGR_SM_InitStyleString(hSM, NULL);
			
	OGRStyleToolH hST;
			
	/***** hi *****/
			
	hST = OGR_ST_Create(OGRSTCSymbol);
	OGR_ST_SetParamStr(hST,OGRSTSymbolId, "\""PACKAGE_WWW"/images/hi.png\"");
	OGR_ST_SetParamStr(hST,OGRSTSymbolSize, "2.0");
	OGR_SM_AddPart (hSM, hST);
	OGR_ST_Destroy(hST);

	OGR_SM_AddStyle(hSM, "@hi", NULL);
	
	/***** lo *****/
			
	hST = OGR_ST_Create(OGRSTCSymbol);
	OGR_ST_SetParamStr(hST,OGRSTSymbolId, "\""PACKAGE_WWW"/images/lo.png\"");
	OGR_ST_SetParamStr(hST,OGRSTSymbolSize, "2.0");
	OGR_SM_AddPart (hSM, hST);
	OGR_ST_Destroy(hST);

	OGR_SM_AddStyle(hSM, "@lo", NULL);
			
	OGR_SM_Destroy(hSM);
	OGR_L_SetStyleTableDirectly(hLayernew, hSTBL);
	
	/***** cleanup *****/

	MWTree_delete_all (&t);

	return;
}
