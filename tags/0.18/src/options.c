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
#include <unistd.h>

#include "options.h"
#include "error.h"

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
	options *o)
{
	int opt;
	
	while (0 < (opt = getopt(argc, argv, "awg:u:v:U:V:m:i:s:k:t:z:h"))) {
		
		switch (opt) {
			case 'w':
				o->wind = 1;
				break;
			
			case 'a':
				o->and = 1;
				break;
			
			case 'g':
				if (!o->wind)
					o->gribfile = optarg;
				break;
			
			case 'u':
				if (o->wind)
					o->ugribfile = optarg;
				break;
			
			case 'v':
				if (o->wind)
					o->vgribfile = optarg;
				break;
			
			case 'm':
				o->gribmsg = atof(optarg);
				break;
			
			case 'U':
				o->ugribmsg = atof(optarg);
				break;
			
			case 'V':
				o->vgribmsg = atof(optarg);
				break;
			
			case 'i':
				o->interval = atof(optarg);
				break;
			
			case 's':
				o->scalename = optarg;
				break;
			
			case 'k':
				o->kmlfile = optarg;
				break;
			
			case 't':
				o->tiffile = optarg;
				break;
			
			case 'z':
				o->kmzfile = optarg;
				break;
			
			case 'h':
			case '?':
			default:
				fprintf(stderr,
								"USAGE: %s <-g grib file> [-m grib msg] <-i interval> <-s color scale>\n"
								"<-k kml file> <-z kmz file> OR <-t <tiff file>\n", argv[0]);
				fprintf(stderr,
								"USAGE: %s -w <-u u wind grib file> <-v v wind grib file>\n"
								"[-U u grib msg] [-V v grib msg] <-i interval> <-s color scale>\n"
								"<-k kml file> <-z kmz file> OR <-t <tiff file>\n", argv[0]);
				fprintf(stderr,
								"USAGE: %s -a <-u data grib file> <-v 0/1 grib file>\n"
								"[-U data grib msg] [-V 0/1 grib msg] <-i interval> <-s color scale>\n"
								"<-k kml file> <-z kmz file> OR <-t <tiff file>\n", argv[0]);
				exit(EXIT_FAILURE);
		}
	}
	
	if (!o->wind && !o->gribmsg)
		o->gribmsg = 1;
	
	else if (o->wind ||o->wind ) {
		if (!o->ugribmsg)
			o->ugribmsg = 1;
		if (!o->vgribmsg)
			o->vgribmsg = 1;
	}
		
	
	if (!o->wind && (!o->gribfile || !o->interval || !o->scalename ||
									(!o->kmlfile && !o->tiffile))) {
		fprintf(stderr,
						"USAGE: %s <-g grib file> <-m grib msg> <-i interval> <-s color scale>\n"
						"<-k kml file> <-z kmz file> OR <-t <tiff file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	else if (o->wind && (!o->ugribfile || !o->vgribfile || !o->interval || !o->scalename || 
											(!o->kmlfile && !o->tiffile))) {
	
		fprintf(stderr,
						"USAGE: %s -w <-u u wind grib file> <-v v wind grib file>\n"
						"[-U u grib msg] [-V v grib msg] <-i interval> <-s color scale>\n"
						"<-k kml file> <-z kmz file> OR <-t <tiff file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	else if (o->and && (!o->ugribfile || !o->vgribfile || !o->interval || !o->scalename || 
											(!o->kmlfile && !o->tiffile))) {
	
		fprintf(stderr,
						"USAGE: %s -a <-u data grib file> <-v 0/1 grib file>\n"
						"[-U data grib msg] [-V 0/1 grib msg] <-i interval> <-s color scale>\n"
						"<-k kml file> <-z kmz file> OR <-t <tiff file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	return;
}
