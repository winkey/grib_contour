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
 
#ifndef _STYLE_H
#define _STYLE_H


/*******************************************************************************
	function to add a style table to a dataset
*******************************************************************************/

void add_ds_style(OGRDataSourceH hDS, color_scale *cscales);

void add_features_style(
	OGRLayerH hLayer,
	color_scale *cscales);

#endif /* STYLE_H */

 
