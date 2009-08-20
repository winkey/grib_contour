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

#define _XOPEN_SOURCE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#include "options.h"
#include "error.h"

#define DEBUG 1

void usage(char *appname, int type) {
	switch (type) {
		case 'g':
			fprintf(stderr,
							"USAGE: %s ( <-g grib file> [-m grib msg] )... <-i interval> [-I]\n"
							"<-s color scale> \[-S scale multiplyer] ( ( <-k kml file> AND \n"
							"<-z kmz file> ) OR <-t <tiff file> )\n\n", appname);
			break;
		
		case 'w':
			fprintf(stderr,
							"USAGE: %s -w ( <-u u wind grib file> <-v v wind grib file>\n"
							"[-U u grib msg] [-V v grib msg] )... <-i interval> [-I]\n"
							"<-s color scale> [-S scale multiplyer] ( ( <-k kml file> AND \n"
							"<-z kmz file> ) OR <-t <tiff file> )\n\n", appname);
			break;
		
		case 'a':
			fprintf(stderr,
							"USAGE: %s -a ( <-u data grib file> <-v 0/1 grib file>\n"
							"[-U data grib msg] [-V 0/1 grib msg] )... <-i interval> [-I]\n"
							"<-s color scale> [-S scale multiplyer] ( ( <-k kml file> AND \n"
							"<-z kmz file> ) OR <-t <tiff file> )\n\n", appname);
			break;
		
		case 'd':
			fprintf(stderr,
							"USAGE: %s -d ( <-u upper grib file> <-v lower grib file>\n"
							"[-U upper grib msg] [-V lower grib msg] )... <-i interval> [-I]\n"
							"<-s color scale> [-S scale multiplyer] ( ( <-k kml file> AND \n"
							"<-z kmz file> ) OR <-t <tiff file> )\n\n", appname);
			break;
		
		default:
			fprintf(stderr,
							"USAGE: %s ( <-g grib file> [-m grib msg] )... <-i interval> [-I]\n"
							"<-s color scale> \[-S scale multiplyer] ( ( <-k kml file> AND \n"
							"<-z kmz file> ) OR <-t <tiff file> )\n\n", appname);
			fprintf(stderr,
							"USAGE: %s -w ( <-u u wind grib file> <-v v wind grib file>\n"
							"[-U u grib msg] [-V v grib msg] )... <-i interval> [-I]\n"
							"<-s color scale> [-S scale multiplyer] ( ( <-k kml file> AND \n"
							"<-z kmz file> ) OR <-t <tiff file> )\n\n", appname);
			fprintf(stderr,
							"USAGE: %s -a ( <-u data grib file> <-v 0/1 grib file>\n"
							"[-U data grib msg] [-V 0/1 grib msg] )... <-i interval> [-I]\n"
							"<-s color scale> [-S scale multiplyer] ( ( <-k kml file> AND \n"
							"<-z kmz file> ) OR <-t <tiff file> )\n\n", appname);
			fprintf(stderr,
							"USAGE: %s -d ( <-u upper grib file> <-v lower grib file>\n"
							"[-U upper grib msg] [-V lower grib msg] )... <-i interval> [-I]\n"
							"<-s color scale> [-S scale multiplyer] ( ( <-k kml file> AND \n"
							"<-z kmz file> ) OR <-t <tiff file> )\n\n", appname);
			break;
	}
	
	return;
}

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
	int i;
	int gcount = 0;
	int ucount = 0;
	int vcount = 0;
	int gmcount = 0;
	int umcount = 0;
	int vmcount = 0;
	
	o->scalecorrection = 1;
	o->finterval = 0;
	o->english = 0;
	o->hilo = 0;
	
	while (0 < (opt = getopt(argc, argv, "adwg:u:v:U:V:m:i:Is:S:c:k:t:z:p:q:r:f:l:eHh?"))) {
		
		switch (opt) {
			case 'w':
				o->wind = 1;
				break;
			
			case 'a':
				o->and = 1;
				break;
			
			case 'd':
				o->diff = 1;
				break;
			
			case 'g':
				o->gribfile[gcount] = optarg;
				if (gmcount < gcount)
					gmcount++;
				gcount++;
				if (gcount > 100) {
					fprintf(stderr, "ERROR: only 99 datasets suported\n");
					exit(EXIT_FAILURE);
					
				}
				break;
			
			case 'u':
				o->ugribfile[ucount] = optarg;
				if (umcount < ucount)
					umcount++;
				ucount++;
				if (ucount > 100) {
					fprintf(stderr, "ERROR: only 99 datasets suported\n");
					exit(EXIT_FAILURE);
				}
				break;
			
			case 'v':
				o->vgribfile[vcount] = optarg;
				if (vmcount < vcount)
					vmcount++;
				vcount++;
				if (vcount > 100) {
					fprintf(stderr, "ERROR: only 99 datasets suported\n");
					exit(EXIT_FAILURE);
				}
				break;
			
			case 'm':
				o->gribmsg[gmcount] = atof(optarg);
				(gmcount)++;
				if (gmcount > 100) {
					fprintf(stderr, "ERROR: only 99 datasets suported\n");
					exit(EXIT_FAILURE);
				}
				break;
			
			case 'r':
				strptime (optarg, "%Y%m%d%k", &(o->run));
				break;
			
			case 'f':
				o->hour = atoi(optarg);
				break;
			
			case 'l':
				o->period = atoi(optarg);
				break;
			
			case 'U':
				o->ugribmsg[umcount] = atof(optarg);
				(umcount)++;
				if (umcount > 100) {
					fprintf(stderr, "ERROR: only 99 datasets suported\n");
					exit(EXIT_FAILURE);
				}
				break;
			
			case 'V':
				o->vgribmsg[vmcount] = atof(optarg);
				(vmcount)++;
				if (vmcount > 100) {
					fprintf(stderr, "ERROR: only 99 datasets suported\n");
					exit(EXIT_FAILURE);
				}
				break;
			
			case 'i':
				o->interval = atof(optarg);
				break;
			
			case 'I':
				o->finterval = 1;
				break;
			
			case 'e':
				o->english = 1;
				break;
			
			case 's':
				o->scalename = optarg;
				break;
			
			case 'S':
				o->scalecorrection = atof(optarg);
				break;
			
			case 'c':
				o->datacorrection = atof(optarg);
				break;
			
			case 'k':
				o->kmlfile = optarg;
				break;
			
			case 't':
				o->tiffile = optarg;
				break;


			case 'H':
				o->hilo = 1;
				break;
					
			case 'p':
				o->pgfile = optarg;
				break;
			
			case 'z':
				o->kmzfile = optarg;
				break;
			case 'q':
				o->quasi = optarg;
				break;
			case 'h':
			case '?':
			default:
				usage(argv[0], 0);
				exit(EXIT_FAILURE);
		}
	}
	
	/***** regular *****/
	
	if (!o->wind && !o->and && !o->diff) {
		if (!gcount) {
			usage(argv[0], 'g');
			exit(EXIT_FAILURE);
		}
		
		if (!o->interval || !o->scalename || (!o->kmlfile && !o->tiffile && !o->pgfile)) {
			usage(argv[0], 'g');
			exit(EXIT_FAILURE);
		}
		
		for (i = 0; i < gcount ; i++) {
			if (!o->gribmsg[i])
				o->gribmsg[i] = 1;
		}
		
		o->count = gcount;
	}
	
	/***** wind *****/
	
	else if (o->wind) {
		if (ucount != vcount) {
			fprintf(stderr,
							"ERROR: you must have the same number of u and v datasets\n");
			usage(argv[0], 'w');
			exit(EXIT_FAILURE);
		}
		
		if (!o->interval || !o->scalename || (!o->kmlfile && !o->tiffile && !o->pgfile)) {
			usage(argv[0], 'w');
			exit(EXIT_FAILURE);
		}
		
		for (i = 0; i < ucount ; i++) {
			if (!o->ugribmsg[i])
				o->ugribmsg[i] = 1;
			if (!o->vgribmsg[i])
				o->vgribmsg[i] = 1;
		}
		
		o->count = ucount;
	}
	
	/***** and *****/
	
	else if (o->and) {
		if (ucount != vcount) {
			fprintf(stderr,
							"ERROR: you must have the same number of u and v datasets\n");
			usage(argv[0], 'a');
			exit(EXIT_FAILURE);
		}
		
		if (!o->interval || !o->scalename || (!o->kmlfile && !o->tiffile && !o->pgfile)) {
			usage(argv[0], 'a');
			exit(EXIT_FAILURE);
		}
		
		for (i = 0; i < ucount ; i++) {
			if (!o->ugribmsg[i])
				o->ugribmsg[i] = 1;
			if (!o->vgribmsg[i])
				o->vgribmsg[i] = 1;
		}
		
		o->count = ucount;
	}
	
	/***** diff *****/
	
	else if (o->diff) {
		if (ucount != vcount) {
			fprintf(stderr,
							"ERROR: you must have the same number of u and v datasets\n");
			usage(argv[0], 'a');
			exit(EXIT_FAILURE);
		}
		
		if (!o->interval || !o->scalename || (!o->kmlfile && !o->tiffile && !o->pgfile)) {
			usage(argv[0], 'a');
			exit(EXIT_FAILURE);
		}
		
		for (i = 0; i < ucount ; i++) {
			if (!o->ugribmsg[i])
				o->ugribmsg[i] = 1;
			if (!o->vgribmsg[i])
				o->vgribmsg[i] = 1;
		}
		
		o->count = ucount;
	}
	
	o->begin.tm_hour = o->run.tm_hour + o->hour;
	o->begin.tm_mday = o->run.tm_mday;
	o->begin.tm_mon = o->run.tm_mon;
	o->begin.tm_year = o->run.tm_year;

	timegm(&(o->begin));

	o->end.tm_hour = o->begin.tm_hour + o->period;
	o->end.tm_mday = o->begin.tm_mday;
	o->end.tm_mon = o->begin.tm_mon;
	o->end.tm_year = o->begin.tm_year;

	timegm(&(o->end));

	return;
}
