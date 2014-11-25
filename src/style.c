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

#include <cpl_conv.h>
#include <ogr_api.h>
#include <ogr_srs_api.h>

#include "options.h"
#include "color.h"
#include "style.h"

/*******************************************************************************
	function to add a style table to a dataset
*******************************************************************************/

void add_ds_style(OGRDataSourceH hDS, color_scale *cscales) {
	
	/***** set the style table *****/
	
	OGRStyleTableH hSTBL = OGR_STBL_Create();
	OGRStyleMgrH hSM = OGR_SM_Create(hSTBL);
	
	color_scale *cscale;
	for (cscale = cscales ; *(cscale->color) ; cscale++) {
		
		/***** clear the current style in the manager *****/
		
		OGR_SM_InitStyleString(hSM, NULL);
		
		char color[10] = {};
		OGRStyleToolH hST;
		
		/***** pen color *****/
		
		snprintf(color, sizeof(color), "#%sff", cscale->color);
		
		hST = OGR_ST_Create(OGRSTCPen);
		OGR_ST_SetParamStr(hST, OGRSTPenColor, color);
		OGR_ST_SetParamNum(hST,OGRSTPenWidth, 2); 
		OGR_ST_SetUnit(hST, OGRSTUPixel, 2);
		OGR_SM_AddPart (hSM, hST);
		OGR_ST_Destroy(hST);

    /***** brush color *****/
			
	  snprintf(color, sizeof(color), "#%saa", cscale->color);
		hST = OGR_ST_Create(OGRSTCBrush);
		OGR_ST_SetParamStr(hST, OGRSTBrushFColor, color);
		OGR_SM_AddPart (hSM, hST);
		OGR_ST_Destroy(hST);
    
		/***** add the style in the manager to the style table *****/
		
		snprintf(color, sizeof(color), "@%s", cscale->color);
		OGR_SM_AddStyle(hSM, color, NULL);
		
	}
	
	OGR_SM_Destroy(hSM);
	OGR_DS_SetStyleTableDirectly(hDS, hSTBL);
}



void add_features_style(
	OGRLayerH hLayer,
	color_scale *cscales)
{
	OGRFeatureH hFeat;
	double value;
					
	OGR_L_ResetReading(hLayer);

	/***** loop while theres features *****/
			
	while((hFeat = OGR_L_GetNextFeature(hLayer))) {
	
		CPLErrorReset();

		/***** flatten to 2d,                    *****/
		/***** i have this here cause its a loop *****/
		/***** and i don't want to add another   *****/
		
		// OGR_G_FlattenTo2D(OGR_F_GetGeometryRef(hFeat));

		/***** the second field contains the data value *****/
		
		value = OGR_F_GetFieldAsDouble(hFeat, 1);
		
		/***** set color *****/
		
		char name[20] = {};
		snprintf(name, sizeof(name), "@%s", color_checkscale(cscales, value));
		
		OGR_F_SetStyleString(hFeat, name);
		
		OGR_L_SetFeature (hLayer, hFeat);

		/***** cleanup *****/
		
		OGR_F_Destroy(hFeat);
		
	}
	
	return;
}
