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
 
#ifndef _OPTIONS_H
#define _OPTIONS_H


typedef struct {
	int wind;
	int and;
	int diff;
	int count;
	char *gribfile[100];
	char *ugribfile[100];
	char *vgribfile[100];
	float gribmsg[100];
	float ugribmsg[100];
	float vgribmsg[100];
	float interval;
	int finterval;
	int english;
	char *scalename;
	float scalecorrection;
	char *kmlfile;
	char *kmzfile;
	char *tiffile;
	char *quasi;
} options;

/*******************************************************************************
	function to parse the program options

args:
						argc		main()s argc argument
						argv		main()s argv argument
						o				pointer to the options struct

returns:
						nothing
*******************************************************************************/

void get_options(
	int argc,
	char ** argv,
	options *o);


#endif /* _OPTIONS_H */

