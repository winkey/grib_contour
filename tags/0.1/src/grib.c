/***************************************************************************
 *            grib.c
 *
 *  Wed Jan 16 11:25:01 2008
 *  Copyright  2008  winkey
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
#include <string.h>
#include <errno.h>

#include "grib.h"

#define DEBUG 1

/*******************************************************************************
	function to open the grib file

	args:
							gribfile		the filename of the gribfile to open
							msg					the grib message to decode
							unit				unit type to decode to 'e' or 'm'
	
	returns:
							file pointer to the stream to read
*******************************************************************************/

FILE *grib_open(
	char *gribfile,
	float msg,
	char unit)
{
	FILE *result = NULL;
	char cmd[1000] = {};
	
	snprintf (cmd, sizeof(cmd),
						"degrib -in \"%s\" -out stdout -C -Unit %c -msg %f -Csv",
						gribfile, unit, msg);
	
	if (!(result = popen(cmd, "r"))) {
		fprintf(stderr, "ERROR: grib_open: %s", strerror(errno));
		exit(EXIT_FAILURE);
	}
	
	return result;
}

/*******************************************************************************
	function to read a gds info line
*******************************************************************************/
size_t grib_gds(
	char *line,
	gds_t *gds)
{
	size_t result = 0;
	char junk[21];
	
	if (1 == sscanf(line, "Number of Points | %i", &(gds->Npoints))) {
		result = gds->Npoints;
		if (DEBUG) fprintf (stderr, "points %i\n", gds->Npoints);
	}
	
	else if (1 == sscanf(line, "Projection Type | %i", &(gds->proj))) {
		if (DEBUG) fprintf (stderr, "proj %i\n", gds->proj);
	}
	
	else if (2 == sscanf(line, "Radius | %f (%20[a-zA-Z])", &(gds->radius), gds->radius_units)) {
		if (DEBUG) fprintf (stderr, "radius %f\n", gds->radius);
	}
	
	else if (1 == sscanf(line, "Nx (Number of points on parallel) | %i", &(gds->Nx))) {
		if (DEBUG) fprintf (stderr, "Nx %i\n", gds->Nx);
	}
	
	else if (1 == sscanf(line, "Ny (Number of points on meridian) | %i", &(gds->Ny))) {
		if (DEBUG) fprintf (stderr, "Ny %i\n", gds->Ny);
	}
	
	else if (1 == sscanf(line, "Lat1 | %f", &(gds->Lat1))) {
		if (DEBUG) fprintf (stderr, "Lat1 %f\n", gds->Lat1);
	}
	
	else if (1 == sscanf(line, "Lon1 | %f", &(gds->Lon1))) {
		if (DEBUG) fprintf (stderr, "Lon1 %f\n", gds->Lon1);
	}
	
	else if (1 == sscanf(line, "Lat2 | %f", &(gds->Lat2))) {
		if (DEBUG) fprintf (stderr, "Lat2 %f\n", gds->Lat2);
	}
	
	else if (1 == sscanf(line, "Lon2 | %f", &(gds->Lon2))) {
		if (DEBUG) fprintf (stderr, "Lon2 %f\n", gds->Lon2);
	}
	
	else if (2 == sscanf(line, "Dx | %f (%20[a-zA-Z])", &(gds->Dx), gds->Dx_units)) {
		if (DEBUG) fprintf (stderr, "Dx %f\n", gds->Dx);
	}
	
	else if (2 == sscanf(line, "Dy | %f (%20[a-zA-Z])", &(gds->Dy), gds->Dy_units)) {
		if (DEBUG) fprintf (stderr, "Dy %f\n", gds->Dy);
	}
	
	else if (1 == sscanf(line, "Output grid, scan i/x direction | %20[a-zA-Z]", junk)) {
		if (strcmp(junk, "positive"))
			gds->Dx *= -1;
		if (DEBUG) fprintf (stderr, "Dx %f\n", gds->Dx);
	}
	
	else if (1 == sscanf(line, "Output grid, scan j/y direction | %20[a-zA-Z]", junk)) {
		if (strcmp(junk, "positive"))
			gds->Dy *= -1;
		if (DEBUG) fprintf (stderr, "Dy %f\n", gds->Dy);
	}
	
	else if (1 == sscanf(line, "MeshLat | %f", &(gds->meshlat))) {
		if (DEBUG) fprintf (stderr, "meshlat %f\n", gds->meshlat);
	}
	
	else if (1 == sscanf(line, "OrientLon | %f", &(gds->orientlon))) {
		if (DEBUG) fprintf (stderr, "orientlon %f\n", gds->orientlon);
	}
	
	else if (1 == sscanf(line, "Tangent Lat1 | %f", &(gds->tan_Lat1))) {
		if (DEBUG) fprintf (stderr, "tan_Lat1 %f\n", gds->tan_Lat1);
	}
	
	else if (1 == sscanf(line, "Tangent Lat2 | %f", &(gds->tan_Lat2))) {
		if (DEBUG) fprintf (stderr, "tan_Lat2 %f\n", gds->tan_Lat2);
	}
	
	else if (1 == sscanf(line, "Southern Lat | %f", &(gds->S_lat))) {
		if (DEBUG) fprintf (stderr, "S_lat %f\n", gds->S_lat);
	}
	else if (1 == sscanf(line, "Southern Lon | %f", &(gds->S_lon))) {
		if (DEBUG) fprintf (stderr, "S_lon %f\n", gds->S_lon);
	}
	
	return result;
}

/*******************************************************************************
	function to read a grib file
	
	args:
							fp		file pointer to the stream to read
							gds		pointer to the gds struct to store the gds info in

	returns:
							pointer to the newly allocated raster data
*******************************************************************************/

float *grib_read(
	FILE *fp,
	gds_t *gds)
{
	float *result = NULL;
	
	char line[1000];
	int x, y;
	float lat, lon, val;
	
	while (fgets(line, sizeof(line), fp)) {
		
		/***** is it a point? *****/
		
		if (result && 5 == sscanf(line, "%i, %i, %f, %f, %f", &x, &y, &lat, &lon, &val)) {
			/*if (x > 360)
				x -= 360;
			else
				x += 360;
			*/
			result[(gds->Nx * (y - 1)) + (x - 1)] = val;
		}
		
		/***** is it a GDS line? *****/
		
		else if (!strncmp (line, "GDS | ", 6))
			if (grib_gds(line + 6, gds))
				if (!(result = malloc(sizeof(float) * gds->Npoints))) {
					fprintf(stderr, "ERROR: grib_read: %s", strerror(errno));
					exit(EXIT_FAILURE);
				}
	}
	
	return result;
}