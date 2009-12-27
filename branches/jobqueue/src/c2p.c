/***************************************************************************
 *            c2p.c
 *
 *  Thu Aug 27 09:31:45 2009
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
#include "c2p.h"

#define DEBUG 0

/*******************************************************************************
 Function to close a open ring that intersects the envelope
 by takeing the shortest diststance around the envelope
*******************************************************************************/

int CloseRing(OGRGeometryH hGeom,
              OGREnvelope hEnv)
{
  
  if (DEBUG)
    fprintf (stderr, "CloseRing()\n");
  
  int result = 0;
  int nPoints = OGR_G_GetPointCount(hGeom);
  double x1, y1, z1;
  double x2, y2, z2;
  
  /***** make point geometrys out of the end points *****/
  
  OGR_G_GetPoint(hGeom, 0, &x1, &y1, &z1);
  OGRGeometryH hGeomPP1 = OGR_G_CreateGeometry(wkbPoint);
  OGR_G_SetPoint_2D (hGeomPP1, 0, x1, y1);
  OGRGeometryH hGeomP1 = OGR_G_Buffer(hGeomPP1, .3, 8);
               
  OGR_G_GetPoint(hGeom, nPoints - 1, &x2, &y2, &z2);
  OGRGeometryH hGeomPP2 = OGR_G_CreateGeometry(wkbPoint);
  OGR_G_SetPoint_2D (hGeomPP2, 0, x2, y2);
  OGRGeometryH hGeomP2 = OGR_G_Buffer(hGeomPP2, .3, 8);

  OGRGeometryH hGeomIntersect1 = NULL;
  OGRGeometryH hGeomIntersect2 = NULL;

  double xInt1, yInt1, zInt1;
  double xInt2, yInt2, zInt2;
  
  /***** we also want the 4 sides as linestring geoms *****/

  OGRGeometryH hGeomEnvLeft = OGR_G_CreateGeometry(wkbLineString);
  OGR_G_AddPoint_2D(hGeomEnvLeft, hEnv.MinX, hEnv.MaxY);
  OGR_G_AddPoint_2D(hGeomEnvLeft, hEnv.MinX, hEnv.MinY);
	
  OGRGeometryH hGeomEnvBottom = OGR_G_CreateGeometry(wkbLineString);
  OGR_G_AddPoint_2D(hGeomEnvBottom, hEnv.MinX, hEnv.MinY);
	OGR_G_AddPoint_2D(hGeomEnvBottom, hEnv.MaxX, hEnv.MinY);

  OGRGeometryH hGeomEnvRight = OGR_G_CreateGeometry(wkbLineString);
  OGR_G_AddPoint_2D(hGeomEnvRight, hEnv.MaxX, hEnv.MinY);
  OGR_G_AddPoint_2D(hGeomEnvRight, hEnv.MaxX, hEnv.MaxY);
	
  OGRGeometryH hGeomEnvTop = OGR_G_CreateGeometry(wkbLineString);
  OGR_G_AddPoint_2D(hGeomEnvTop, hEnv.MaxX, hEnv.MaxY);
	OGR_G_AddPoint_2D(hGeomEnvTop, hEnv.MinX, hEnv.MaxY);
  
  OGRGeometryH env[4] = {hGeomEnvLeft, hGeomEnvBottom, hGeomEnvRight, hGeomEnvTop};

  /***** loop though the envelope sides *****/

  //OGR_G_DumpReadable(hGeom, stdout, "before ");
  
  int i;
  for (i = 0 ; i < 4 && !result ; i++) {

    /***** check the envelope side against the first end for intersection ******/
    
    if (OGR_G_Intersects(env[i], hGeomP1)) {

      /***** correct the first linesting point *****

      if (i % 2) {

        ***** top/bottom *****
        
        hGeomIntersect1 = OGR_G_Intersection(env[i], hGeomP1);
        OGR_G_GetPoint(hGeomIntersect1, 0, &xInt1, &yInt1, &zInt1);
        OGR_G_GetPoint(hGeomIntersect1, OGR_G_GetPointCount(hGeomIntersect1) - 1,
                       &xInt2, &yInt2, &zInt2);
        OGR_G_SetPoint(hGeom, 0, (xInt1 + xInt2) * .5, yInt1, z1);
        x1 = (xInt1 + xInt2) * .5;
      }
      else {

        ***** left/right *****

        hGeomIntersect1 = OGR_G_Intersection(env[i], hGeomP1);
        OGR_G_GetPoint(hGeomIntersect1, 0, &xInt1, &yInt1, &zInt1);
        OGR_G_GetPoint(hGeomIntersect1, OGR_G_GetPointCount(hGeomIntersect1) - 1,
                       &xInt2, &yInt2, &zInt2);
        OGR_G_SetPoint(hGeom, 0, xInt1, (yInt1 + yInt2) * .5, z1);
        y1 = (yInt1 + yInt2) * .5;
      }

      ***** loop though the sides *****/

      int j;
      for (j = 0 ; j < 4  && !result ; j++) {

        /***** check the envelope side against the last end for intersection ******/
    
        if (OGR_G_Intersects(env[j], hGeomP2)) {

          /***** correct the last linesting point *****

          if (j % 2) {

            ***** top/bottom *****
            
            hGeomIntersect2 = OGR_G_Intersection(env[i], hGeomP2);
            OGR_G_GetPoint(hGeomIntersect2, 0, &xInt1, &yInt1, &zInt1);
            OGR_G_GetPoint(hGeomIntersect2, OGR_G_GetPointCount(hGeomIntersect2) - 1,
                           &xInt2, &yInt2, &zInt2);
            OGR_G_SetPoint(hGeom, nPoints - 1, (xInt1 + xInt2) * .5, yInt1, z1);
            x2 = (xInt1 + xInt2) * .5;
          }
          else {

            ***** left/right *****

            hGeomIntersect2 = OGR_G_Intersection(env[i], hGeomP2);
            OGR_G_GetPoint(hGeomIntersect2, 0, &xInt1, &yInt1, &zInt1);
            OGR_G_GetPoint(hGeomIntersect2, OGR_G_GetPointCount(hGeomIntersect2) - 1,
                           &xInt2, &yInt2, &zInt2);
            OGR_G_SetPoint(hGeom, nPoints - 1, xInt1, (yInt1 + yInt2) * .5, z1);
            y2 = (yInt1 + yInt2) * .5;
          }

          ***** same side *****/
          
          if (i - j == 0)
            OGR_G_SetPoint(hGeom, nPoints, x1, y1, z1);

          /***** counterclockwise 1 *****/
          
          else if (i - j == 1 || (i == 0 && j == 3)) {
            OGR_G_SetPoint(hGeom, nPoints, OGR_G_GetX(env[j], 1), OGR_G_GetY(env[j], 1), z1);
            OGR_G_SetPoint(hGeom, nPoints + 1, x1, y1, z1);
          }
          
          /***** clockwise 1 *****/
          
          else if (j - i == 1 || (j == 0 && i == 3)) {
            OGR_G_SetPoint(hGeom, nPoints, OGR_G_GetX(env[j], 0), OGR_G_GetY(env[j], 0), z1);
            OGR_G_SetPoint(hGeom, nPoints + 1, x1, y1, z1);
          }

          else {

            int c = j - 1;
            int cc = i - 1;
            if (c < 0)
              c = 3;
            if ((cc < 1))
              cc = 3;
            
            /***** counterclockwise 2 *****/
            
            if (OGR_G_Distance(env[cc], hGeom) < OGR_G_Distance(env[c], hGeom)) {
              OGR_G_SetPoint(hGeom, nPoints, OGR_G_GetX(env[cc], 0), OGR_G_GetY(env[cc], 0), z1);
              //double length = OGR_G_GetX(env[cc], 1) - OGR_G_GetX(env[cc], 0);
              //OGR_G_SetPoint(hGeom, nPoints + 1, OGR_G_GetX(env[cc], 0) + (length / 4), OGR_G_GetY(env[c], 1), z1);
              //OGR_G_SetPoint(hGeom, nPoints + 2, OGR_G_GetX(env[cc], 0) + (length / 2), OGR_G_GetY(env[c], 1), z1);
              //OGR_G_SetPoint(hGeom, nPoints + 3, OGR_G_GetX(env[cc], 0) + (length / 2) + (length / 4), OGR_G_GetY(env[c], 1), z1);
              OGR_G_SetPoint(hGeom, nPoints + 1, OGR_G_GetX(env[cc], 1), OGR_G_GetY(env[cc], 1), z1);
              OGR_G_SetPoint(hGeom, nPoints + 2, x1, y1, z1);
            }

            /***** clockwise 2 *****/

            else {
              OGR_G_SetPoint(hGeom, nPoints, OGR_G_GetX(env[c], 1), OGR_G_GetY(env[c], 1), z1);
              //double length = OGR_G_GetX(env[c], 0) - OGR_G_GetX(env[c], 1);
              //OGR_G_SetPoint(hGeom, nPoints + 1, OGR_G_GetX(env[c], 1) + (length / 4), OGR_G_GetY(env[c], 1), z1);
              //OGR_G_SetPoint(hGeom, nPoints + 2, OGR_G_GetX(env[c], 1) + (length / 2), OGR_G_GetY(env[c], 1), z1);
              //OGR_G_SetPoint(hGeom, nPoints + 3, OGR_G_GetX(env[c], 1) + (length / 2) + (length / 4), OGR_G_GetY(env[c], 1), z1);
              OGR_G_SetPoint(hGeom, nPoints + 1, OGR_G_GetX(env[c], 0), OGR_G_GetY(env[c], 0), z1);
              OGR_G_SetPoint(hGeom, nPoints + 2, x1, y1, z1);
            }
          }

          result = 1;
        }
      }
    }
  }

  if (!result)
    fprintf (stderr, "warning unable to close linestring\n");

  //OGR_G_DumpReadable(hGeom, stdout, "after ");
  
  /***** cleanup *****/

  OGR_G_DestroyGeometry(hGeomP1);
	OGR_G_DestroyGeometry(hGeomP2);
  OGR_G_DestroyGeometry(hGeomPP1);
	OGR_G_DestroyGeometry(hGeomPP2);
  if (hGeomIntersect1)
    OGR_G_DestroyGeometry(hGeomIntersect1);
  if (hGeomIntersect2)
    OGR_G_DestroyGeometry(hGeomIntersect2);
  OGR_G_DestroyGeometry(hGeomEnvLeft);
  OGR_G_DestroyGeometry(hGeomEnvRight);
  OGR_G_DestroyGeometry(hGeomEnvBottom);
  OGR_G_DestroyGeometry(hGeomEnvTop);

  return result;
}




/*******************************************************************************
 function to turn a linestring into a polygon
*******************************************************************************/

OGRGeometryH Line2Poly(OGRGeometryH hGeomLine)
{
  if (DEBUG)
    fprintf (stderr, "Line2Poly()\n");
  
  OGRGeometryH hGeomLR = OGR_G_CreateGeometry(wkbLinearRing);

  int i;
	for (i = 0; i < OGR_G_GetPointCount(hGeomLine); i++) {
		double x, y, z;
		OGR_G_GetPoint (hGeomLine, i, &x, &y, &z);
		OGR_G_SetPoint (hGeomLR, i, x, y, z);
	}

  OGRGeometryH hGeomPoly = OGR_G_CreateGeometry(wkbPolygon);
	OGR_G_AddGeometryDirectly(hGeomPoly, hGeomLR);

  return hGeomPoly;
}

/*******************************************************************************
	MWTree function to cmp 2 features for contains
*******************************************************************************/

int tree_cmp(
	void *data1,
	void *data2)
{
	if (DEBUG)
    fprintf (stderr, "tree_cmp()\n");
  int result = 0;

	OGRGeometryH hGeom1 = OGR_F_GetGeometryRef(data1);
	OGRGeometryH hGeom2 = OGR_F_GetGeometryRef(data2);

	/***** contains not contains *****/
	
	if (OGR_G_Contains( hGeom1, hGeom2))
		result = 1;
	else if (OGR_G_Contains( hGeom2, hGeom1))
		result = -1;
	
	return result;
}


/*******************************************************************************
	MWTree function to free the features stored in it
*******************************************************************************/

void tree_free(void *data) {
	OGR_F_Destroy(data);
}

/*******************************************************************************
	traverse function to iterate the tree and add the polys as outer and inner rings
********************************************************************************/

void * tree_traverse_rings(
	MWTree *t,
	MWTree_node *n,
	void *data,
	void *extra)
{
	OGRFeatureH hFeat = data;
  OGRLayerH hLayer = extra;

  if (DEBUG)
    fprintf (stderr, "tree_traverse_rings()\n");
  /***** get the poly geometry from the feature *****/
  
  OGRGeometryH hGeom = OGR_F_GetGeometryRef(hFeat);
  
  /***** get the LR geometry from the poly geometry *****/
    
  OGRGeometryH hGeomLR = OGR_G_GetGeometryRef(hGeom, 0);

  double x, y, z;
  OGR_G_GetPoint (hGeomLR, 0, &x, &y, &z);
  printf ("node z = %g\n", z);
  
	/***** go though the nodes children they are interior rings *****/
	int j = 1;
	DLList_node *c;
	for (c = n->children.head ; c ; c = c->next, j++) {
		MWTree_node *cnode = c->data;
		OGRFeatureH hFeatChild = cnode->data;

    /***** get the poly geometry from the child feature *****/
    
    OGRGeometryH hGeomChild = OGR_F_GetGeometryRef(hFeatChild);

    /***** get the LR geometry from the child poly geometry *****/
    
    OGRGeometryH hGeomChildLR = OGR_G_GetGeometryRef(hGeomChild, 0);

    OGR_G_GetPoint (hGeomChildLR, 0, &x, &y, &z);
    printf ("child z = %g\n", z);

    /***** cut all the geometry out of the root *****/
    if (n == t->root) {
      OGRGeometryH hGeomSymDiff = OGR_G_SymmetricDifference(hGeom, hGeomChild);
      OGRGeometryH hGeomNewroot = OGR_G_Intersection(hGeomSymDiff, hGeom);
      OGR_F_SetGeometryDirectly(hFeat, hGeomNewroot);
      OGR_G_DestroyGeometry(hGeomSymDiff);
      hGeom = hGeomNewroot;
    }

    else {
      /***** add the child LR geometry to the geometry as an inner ring *****/
    
      OGR_G_AddGeometry (hGeom, hGeomChildLR);
    }
    
  }

  //OGR_F_SetGeometryDirectly(hFeat, hGeom);

  /****** replace the feature in the layer *****/

  OGR_L_SetFeature (hLayer, hFeat);

  
  return NULL;
}
		

/*******************************************************************************'
  function convert a contoured linestring layer into a layer of polygons
*******************************************************************************/

OGRLayerH c2p (
	OGRDataSourceH hogrDS,
	OGRLayerH hLayer,
  OGRSpatialReferenceH hSRS)
{

  if (DEBUG)
    fprintf (stderr, "c2p()\n");
  MWTree t = {};
  t.cmp = tree_cmp;
	t.free = tree_free;
	
	OGRGeometryH hGeom = NULL;
	
  /***** create the new polygon layer *****/
	
	OGRLayerH hPolyLayer;
	if (!(hPolyLayer = OGR_DS_CreateLayer(hogrDS, "polygon", hSRS, wkbPolygon, NULL)))
		ERROR("c2p OGR_DS_CreateLayer");

  /***** copy the feild defn's *****/

  OGRFeatureDefnH hFeatDefn = OGR_L_GetLayerDefn(hLayer);

  int i;
  for (i = 0 ; i < OGR_FD_GetFieldCount(hFeatDefn) ; i++) {
    OGRFieldDefnH hFieldDefn = OGR_FD_GetFieldDefn(hFeatDefn, i);
    if (OGR_L_CreateField(hPolyLayer, hFieldDefn, i))
      ERROR("c2p OGR_L_CreateField");
  }
  
	/***** get the extent of the layer *****/
	
	OGREnvelope hEnv;
	OGR_L_GetExtent(hLayer, &hEnv, 1);

	/***** turn the extent to a geom *****/

	hGeom = OGR_G_CreateGeometry(wkbLinearRing);
	
	OGR_G_AddPoint_2D(hGeom, hEnv.MinX, hEnv.MinY);
	OGR_G_AddPoint_2D(hGeom, hEnv.MinX, hEnv.MaxY);
	OGR_G_AddPoint_2D(hGeom, hEnv.MaxX, hEnv.MaxY);
	OGR_G_AddPoint_2D(hGeom, hEnv.MaxX, hEnv.MinY);
	OGR_G_AddPoint_2D(hGeom, hEnv.MinX, hEnv.MinY);

  OGRFeatureH hFeatEnv;
	hFeatEnv = OGR_F_Create(OGR_L_GetLayerDefn(hPolyLayer));

  OGRGeometryH hGeomPoly = OGR_G_CreateGeometry(wkbPolygon);
	OGR_G_AddGeometryDirectly(hGeomPoly, hGeom);
  
	OGR_F_SetGeometryDirectly(hFeatEnv, hGeomPoly);
	MWTree_insert (&t, hFeatEnv);
	
	/***** loop while theres features *****/
	
	OGR_L_ResetReading(hLayer);
	OGRFeatureH hFeat;
	while((hFeat = OGR_L_GetNextFeature(hLayer))) {
		CPLErrorReset();
		hGeom = OGR_F_GetGeometryRef(hFeat);
		
    /***** is it already a closed ring? *****/
    
		if (OGR_G_IsRing(hGeom) && OGR_G_IsSimple(hGeom)) {
			
      /***** create the new poly feature *****/
      
      OGRFeatureH hFeatPoly = OGR_F_Create(OGR_L_GetLayerDefn(hPolyLayer));

      /***** turn the linestring into a polygon *****/
      
      OGRGeometryH hGeomPoly = Line2Poly(hGeom);

      /***** add the polygon to the new feature *****/
      
      OGR_F_SetGeometryDirectly(hFeatPoly, hGeomPoly);

      /***** copy the fields *****/

      for (i = 0 ; i < OGR_F_GetFieldCount(hFeat) ; i++) {
        OGRField *hField = OGR_F_GetRawFieldRef(hFeat, i);
        OGR_F_SetFieldRaw(hFeatPoly, i, hField);
      }
    
      /***** add the new feature to the layer *****/

      OGR_L_CreateFeature (hPolyLayer, hFeatPoly);
      
      /***** add the new feasture to the mway tree *****/
      
			if (!MWTree_insert(&t, hFeatPoly))
				ERROR("c2p MWTree_insert");
		}

		/***** try to close the linestring *****/

    else if (OGR_G_IsSimple(hGeom) && CloseRing(hGeom, hEnv)) {
      
      /***** create the new poly feature *****/
      
      OGRFeatureH hFeatPoly = OGR_F_Create(OGR_L_GetLayerDefn(hPolyLayer));

      /***** turn the linestring into a polygon *****/
      
      OGRGeometryH hGeomPoly = Line2Poly(hGeom);

      /***** add the polygon to the new feature *****/
      
      OGR_F_SetGeometryDirectly(hFeatPoly, hGeomPoly);
	
      /***** copy the fields *****/

      for (i = 0 ; i < OGR_F_GetFieldCount(hFeat) ; i++) {
        OGRField *hField = OGR_F_GetRawFieldRef(hFeat, i);
        OGR_F_SetFieldRaw(hFeatPoly, i, hField);
      }
      
      /***** add the new feature to the layer *****/

      OGR_L_CreateFeature (hPolyLayer, hFeatPoly);
      
      /***** add the new feasture to the mway tree *****/
      
			if (!MWTree_insert(&t, hFeatPoly))
				ERROR("c2p MWTree_insert");
		}

    /***** cleanup *****/

    OGR_F_Destroy(hFeat);

  }  
      
	/***** fill our new poly layer ****/

  
	MWTree_levelorder(&t, 0, tree_traverse_rings, hPolyLayer);


  
  MWTree_delete_all (&t);
  
	return hPolyLayer;
}

