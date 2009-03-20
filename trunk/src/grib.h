/***************************************************************************
 *            grib.h
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
 
#ifndef _GRIB_H
#define _GRIB_H

/*******************************************************************************
	struct for the gds info in the grib file
*******************************************************************************/

typedef struct {
	int Npoints;
	int proj;
	char shape[21];
	float radius;
	char radius_units[21];
	int Nx;
	int Ny;
	float xDir;
	float yDir;
	float Lat1;
	float Lon1;
	float Lat2;
	float Lon2;
	float Dx;
	char Dx_units[21];
	float Dy;
	char Dy_units[21];
	float meshlat;
	float orientlon;
	float tan_Lat1;
	float tan_Lat2;
	float S_lat;
	float S_lon;
	int missing;
	double missing_value;
} gds_t;

/*******************************************************************************
	enum for grib projection types
*******************************************************************************/

enum {
	GDS_LATLON = 0,
	GDS_MERCATOR = 10,
	GDS_POLAR = 20,
	GDS_LAMBERT = 30,
	GDS_GAUSSIAN_LATLON = 40,
	GDS_ORTHOGRAPHIC = 90,
	GDS_ROTATED_LATLON = 100,
	GDS_EQUATOR_EQUIDIST = 110,
	GDS_AZIMUTH_RANGE = 120
};

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
	char unit);


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
	gds_t *gds);

float *do_grib(
	options *o,
	char *gribfile,
	float gribmsg,
	gds_t *gds);

float *do_wind_grib(
	options *o,
	char *ugribfile,
	char *vgribfile,
	float ugribmsg,
	float vgribmsg,
	gds_t *gds);

float *do_and_grib(
	options *o,
	char *ugribfile,
	char *vgribfile,
	float ugribmsg,
	float vgribmsg,
	gds_t *gds);


#endif /* _GRIB_H */

 
