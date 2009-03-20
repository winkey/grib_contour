## Process this file with automake to produce Makefile.in

## Created by Anjuta

INCLUDES = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" 

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = grib_contour \
	grib_wind_contour\
	fixcolor

fixcolor_SOURCES = \
	fixcolor.c

grib_wind_contour_SOURCES = \
	gdalcode.c         \
	grib.c         \
	ogrcode.c         \
	wind.c         \
	error.h         \
	gdalcode.h         \
	grib.h         \
	ogrcode.h

grib_wind_contour_LDFLAGS = \
	-lgdal               \
	-lweathercalc

grib_contour_SOURCES = \
	main.c        \
	grib.c        \
	gdalcode.c        \
	ogrcode.c        \
	error.h        \
	gdalcode.h        \
	grib.h        \
	ogrcode.h

grib_contour_LDFLAGS = \
	-lgdal

grib_contour_LDADD = 


