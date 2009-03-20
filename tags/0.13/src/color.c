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
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "color.h"
#include "error.h"



/*******************************************************************************
	function to get the scale

	args:
							name				the name of the scale

	returns:
							the scale
	
	NOTE: you must free() the result when your done with it
*******************************************************************************/

color_scale *color_getscale(
	char *name)
{
	char filename[1024];
	FILE *fp;
	char line[1024];
	
	size_t used = 0, alloced = 0;
	
	color_scale *scales = NULL;
	color_scale *temp = NULL;
	
	snprintf(filename, sizeof(filename), "%s/%s.scale", PACKAGE_PKG_DATA_DIR, name);
	
	if (!(fp = fopen(filename, "r")))
		ERROR("color_getscale");
	
	while (fgets(line, sizeof(line), fp)) {
		
		/***** if no memory alocate *****/

		if (!alloced) {
			alloced = 30;
			if (!(scales = malloc (alloced * sizeof(color_scale))))
				ERROR("color_getscale");
		}

		/***** if not enough memory realocate *****/

		else {
			if (alloced < used + 2) {
				alloced *= 2;
				if (!(temp = realloc (scales, alloced * sizeof(color_scale))))
					ERROR("buffer_alloc");
			
				scales = temp;
			}
		}
		
		if (2 == sscanf(line, "%f %6[0-9a-fA-F]", &((scales[used]).value), (scales[used]).color)) {
			scales[used].color[6] = 0;
			used++;
		}
		
		scales[used].value = 0;
		scales[used].color[0] = 0;

	}
	
		 
	fclose(fp);
	
	return scales;
}

/*******************************************************************************
	function to get a color from a scale

	args:
							scales			the scale to check
							value				the value to check for in the scale

	returns:
							the color for the value
*******************************************************************************/
 
char *color_checkscale(
	color_scale *scales,
	float value)
{
	color_scale *scale;
	
	for (scale = scales ;
			 value > scale->value && *((scale + 1)->color) != 0;
			 scale++);
	
	return scale->color;
}

