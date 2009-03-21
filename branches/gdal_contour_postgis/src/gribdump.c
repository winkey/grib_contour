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

#define _ISOC99_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <wind.h>

#include "options.h"
#include "grib.h"
#include "gribdump.h"
#include "error.h"

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

FILE *gribdump_open(
	char *gribfile,
	float msg,
	char unit,
	char *quasi)
{
	FILE *result = NULL;
	char cmd[1000] = {};
	
	snprintf (cmd, sizeof(cmd),
						"gribdump -q \"%s\" \"%s\"",
						quasi, gribfile);
	
	if (!(result = popen(cmd, "r")))
		ERROR("gribdump_open");
	
	return result;
}

/*******************************************************************************
	function to read a gds info line
*******************************************************************************/
size_t gribdump_gds(
	char *line,
	gds_t *gds)
{
	size_t result = 0;
	char junk[21];
	
	if (1 == sscanf(line, " points in grid : %i", &(gds->Npoints))) {
		result = gds->Npoints;
		if (DEBUG) fprintf (stderr, "points %i\n", gds->Npoints);
	}
	
	else if (1 == sscanf(line, " GDS representation type : %i", &(gds->proj))) {
		if (DEBUG) fprintf (stderr, "proj %i\n", gds->proj);
	}
#warning fixme i dont have this info
	else if (2 == sscanf(line, "Radius | %f (%20[a-zA-Z])", &(gds->radius), gds->radius_units)) {
		if (DEBUG) fprintf (stderr, "radius %f\n", gds->radius);
	}
	
	else if (1 == sscanf(line, " GDS Ni : %i", &(gds->Nx))) {
		if (DEBUG) fprintf (stderr, "Nx %i\n", gds->Nx);
	}
	
	else if (1 == sscanf(line, " GDS Nj : %i", &(gds->Ny))) {
		if (DEBUG) fprintf (stderr, "Ny %i\n", gds->Ny);
	}
	
	else if (1 == sscanf(line, " GDS La1 : %f", &(gds->Lat1))) {
		if (DEBUG) fprintf (stderr, "Lat1 %f\n", gds->Lat1);
	}
	
	else if (1 == sscanf(line, " GDS Lo1 : %f", &(gds->Lon1))) {
		if (DEBUG) fprintf (stderr, "Lon1 %f\n", gds->Lon1);
	}
	
	else if (1 == sscanf(line, " GDS La2 : %f", &(gds->Lat2))) {
		if (DEBUG) fprintf (stderr, "Lat2 %f\n", gds->Lat2);
	}
	
	else if (1 == sscanf(line, " GDS Lo2 : %f", &(gds->Lon2))) {
		if (DEBUG) fprintf (stderr, "Lon2 %f\n", gds->Lon2);
	}
#warning fixme no units	
	else if (2 == sscanf(line, " GDS Di : %f (%20[a-zA-Z])", &(gds->Dx), gds->Dx_units)) {
		if (DEBUG) fprintf (stderr, "Dx %f\n", gds->Dx);
	}
#warning fixme no units	
	else if (2 == sscanf(line, " GDS Dj : %f (%20[a-zA-Z])", &(gds->Dy), gds->Dy_units)) {
		if (DEBUG) fprintf (stderr, "Dy %f\n", gds->Dy);
	}
#warning fixme	
	else if (1 == sscanf(line, "Output grid, scan i/x direction | %20[a-zA-Z]", junk)) {
		if (strcmp(junk, "positive")) {
			gds->Dx *= -1;
			gds->xDir = -1;
		}
		else 
			gds->xDir = 1;
		
		if (DEBUG) fprintf (stderr, "Dx %f\n", gds->Dx);
	}
#warning fixme	
	else if (1 == sscanf(line, "Output grid, scan j/y direction | %20[a-zA-Z]", junk)) {
		if (strcmp(junk, "positive")) {
			gds->Dy *= -1;
			gds->yDir = -1;
		}
		else 
			gds->yDir = 1;
		
		if (DEBUG) fprintf (stderr, "Dy %f\n", gds->Dy);
	}
#warning fixme	
	else if (1 == sscanf(line, "MeshLat | %f", &(gds->meshlat))) {
		if (DEBUG) fprintf (stderr, "meshlat %f\n", gds->meshlat);
	}
#warning fixme	
	else if (1 == sscanf(line, "OrientLon | %f", &(gds->orientlon))) {
		if (DEBUG) fprintf (stderr, "orientlon %f\n", gds->orientlon);
	}
#warning fixme	
	else if (1 == sscanf(line, "Tangent Lat1 | %f", &(gds->tan_Lat1))) {
		if (DEBUG) fprintf (stderr, "tan_Lat1 %f\n", gds->tan_Lat1);
	}
#warning fixme	
	else if (1 == sscanf(line, "Tangent Lat2 | %f", &(gds->tan_Lat2))) {
		if (DEBUG) fprintf (stderr, "tan_Lat2 %f\n", gds->tan_Lat2);
	}
#warning fixme	
	else if (1 == sscanf(line, "Southern Lat | %f", &(gds->S_lat))) {
		if (DEBUG) fprintf (stderr, "S_lat %f\n", gds->S_lat);
	}
#warning fixme
	else if (1 == sscanf(line, "Southern Lon | %f", &(gds->S_lon))) {
		if (DEBUG) fprintf (stderr, "S_lon %f\n", gds->S_lon);
	}
	
	return result;
}

/*******************************************************************************
	function to read a info line
*******************************************************************************/
void gribdump_info(
	char *line,
	gds_t *gds)
{
	
	if (1 == sscanf(line, "Missing value management | %i", &(gds->missing))) {
		if (DEBUG) fprintf (stderr, "missing %i\n", gds->missing);
	}
	
	else if (1 == sscanf(line, "Primary missing value | %lg", &(gds->missing_value))) {
		if (DEBUG) fprintf (stderr, "missing_value %lg\n", gds->missing_value);
	}
	
	return;
}

/*******************************************************************************
	function to read a grib file
	
	args:
							fp		file pointer to the stream to read
							gds		pointer to the gds struct to store the gds info in

	returns:
							pointer to the newly allocated raster data
*******************************************************************************/

float *gribdump_read(
	FILE *fp,
	gds_t *gds)
{
	float *result = NULL;
	
	char line[1000];
	int x = 0;
	int y = -1;
	float lat, lon, val;
	
	while (fgets(line, sizeof(line), fp)) {
		
		if (1 == sscanf(line, "Row %i:", &y)) {
			x = 0;
			continue;
		}
		
		if (y > -1) {
			char *endptr = line;
			char *last = line;
			val = strtof(endptr, &endptr);
			while (endptr && endptr != last) {
				result[(gds->Nx * y) + x] = val;
				x++;
				last = endptr;
				val = strtof(endptr, &endptr);
			}
		}
		
		else {
			if (gribdump_gds(line, gds))
				if (!(result = malloc(sizeof(float) * gds->Npoints)))
					ERROR("gribdump_read");
		}
		
	} 
	
	
	return result;
}

float *do_gribdump(
	options *o,
	char *gribfile,
	float gribmsg,
	char *quasi,
	gds_t *gds)
{
	FILE *fp = NULL;
	float *raster;
	int i;
	
  /***** open the grib file *****/
  
	if (o->english) {
		fp = gribdump_open(gribfile, gribmsg, 'e', quasi);
  }
  else {
		fp = gribdump_open(gribfile, gribmsg, 'm', quasi);
  }

  /***** read the grib raster into memory *****/
  
  raster = gribdump_read(fp, gds);
  
	/***** correct the data if specified *****/
	
	if (o->datacorrection != 0.0)
		for (i = 0; i < gds->Npoints ; i++)
			raster[i] += o->datacorrection;
	
	/***** close the grib file *****/
	
	
	pclose(fp);
	
	return raster;
}

float *do_wind_gribdump(
	options *o,
	char *ugribfile,
	char *vgribfile,
	float ugribmsg,
	float vgribmsg,
	char *quasi,
	gds_t *gds)
{
	FILE *Ufp = NULL;
	FILE *Vfp = NULL;
	float *raster;
	float *Uraster = NULL;
	float *Vraster = NULL;
	int i;
	
  /***** open the grib file *****/
	
  if (o->english) {
		Ufp = gribdump_open(ugribfile, ugribmsg, 'e', quasi);
		Vfp = gribdump_open(vgribfile, vgribmsg, 'e', quasi);
	}
  else {
		Ufp = gribdump_open(ugribfile, ugribmsg, 'm', quasi);
		Vfp = gribdump_open(vgribfile, vgribmsg, 'm', quasi);
	}
  
  /***** read the grib raster into memory *****/
  
  Uraster = gribdump_read(Ufp, gds);
  Vraster = gribdump_read(Vfp, gds);
  
	/***** close the grib file *****/
	
	pclose(Ufp);
	pclose(Vfp);
	
	if (!(raster = malloc(sizeof(float) * gds->Npoints)))
		ERROR("do_wind_grib");
	
	for (i = 0; i < gds->Npoints ; i++) {
		if (gds->missing && (Uraster[i] == gds->missing_value || Vraster[i] == gds->missing_value))
			raster[i] = gds->missing_value;
		else
			raster[i] = uv2velocity(Uraster[i], Vraster[i]);
	}

	
	free(Uraster);
	free(Vraster);
	
	return raster;
}

float *do_and_gribdump(
	options *o,
	char *ugribfile,
	char *vgribfile,
	float ugribmsg,
	float vgribmsg,
	char *quasi,
	gds_t *gds)
{
	FILE *Ufp = NULL;
	FILE *Vfp = NULL;
	float *raster;
	float *Uraster = NULL;
	float *Vraster = NULL;
	int i;
	
  /***** open the grib file *****/
	
  if (o->english) {
		Ufp = gribdump_open(ugribfile, ugribmsg, 'e', quasi);
		Vfp = gribdump_open(vgribfile, vgribmsg, 'e', quasi);
	}
  else {
		Ufp = gribdump_open(ugribfile, ugribmsg, 'm', quasi);
		Vfp = gribdump_open(vgribfile, vgribmsg, 'm', quasi);
	}
		
  /***** read the grib raster into memory *****/
  
  Uraster = gribdump_read(Ufp, gds);
  Vraster = gribdump_read(Vfp, gds);
  
	/***** close the grib file *****/
	
	pclose(Ufp);
	pclose(Vfp);
	
	if (!(raster = malloc(sizeof(float) * gds->Npoints)))
		ERROR("do_and_grib");
	
	for (i = 0; i < gds->Npoints ; i++) {
		if (gds->missing && (Uraster[i] == gds->missing_value || Vraster[i] == gds->missing_value))
			raster[i] = gds->missing_value;
		else if ((int)Vraster[i])
			raster[i] = Uraster[i];
		else
			raster[i] = 0.0;
	}

	
	free(Uraster);
	free(Vraster);
	
	return raster;
}

float *do_diff_gribdump(
	options *o,
	char *ugribfile,
	char *vgribfile,
	float ugribmsg,
	float vgribmsg,
	char *quasi,
	gds_t *gds)
{
	FILE *Ufp = NULL;
	FILE *Vfp = NULL;
	float *raster;
	float *Uraster = NULL;
	float *Vraster = NULL;
	int i;
	
  /***** open the grib file *****/
	
  if (o->english) {
		Ufp = gribdump_open(ugribfile, ugribmsg, 'e', quasi);
		Vfp = gribdump_open(vgribfile, vgribmsg, 'e', quasi);
	}
  else {
		Ufp = gribdump_open(ugribfile, ugribmsg, 'm', quasi);
		Vfp = gribdump_open(vgribfile, vgribmsg, 'm', quasi);
	}
		
  /***** read the grib raster into memory *****/
  
  Uraster = gribdump_read(Ufp, gds);
  Vraster = gribdump_read(Vfp, gds);
  
	/***** close the grib file *****/
	
	pclose(Ufp);
	pclose(Vfp);
	
	if (!(raster = malloc(sizeof(float) * gds->Npoints)))
		ERROR("do_diff_grib");
	
	for (i = 0; i < gds->Npoints ; i++) {
		if (gds->missing && (Uraster[i] == gds->missing_value || Vraster[i] == gds->missing_value))
			raster[i] = gds->missing_value;
		else {
			raster[i] = Uraster[i] - Vraster[i];
		
		}
	}

	
	free(Uraster);
	free(Vraster);
	
	return raster;
}
