## Process this file with automake to produce Makefile.in

## Created by Anjuta

www = @WWW@
wwwdisk = @WWWDISK@

INCLUDES = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	-DPACKAGE_PKG_DATA_DIR=\""$(pkgdatadir)"\" 
	
AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = grib_contour \
	grib_wind_contour

grib_wind_contour_SOURCES = \
	buffer.c           \
	buffer.h           \
	color.c           \
	color.h           \
	error.h           \
	gdalcode.c           \
	gdalcode.h           \
	grib.c           \
	grib.h           \
	kml.c           \
	kml.h           \
	ogrcode.c           \
	ogrcode.h           \
	wind.c           \
	zipbuffer.c           \
	zipbuffer.h

grib_wind_contour_LDFLAGS =        \
	-lweathercalc        \
	-lgdal        \
	-lzip

grib_contour_SOURCES = \
	main.c        \
	grib.c        \
	gdalcode.c        \
	ogrcode.c        \
	error.h        \
	gdalcode.h        \
	grib.h        \
	ogrcode.h        \
	kml.c        \
	buffer.c        \
	zipbuffer.c        \
	zipbuffer.h        \
	buffer.h        \
	color.c        \
	color.h        \
	kml.h

grib_contour_LDFLAGS = \
	-lgdal          \
	-lzip

grib_contour_LDADD = 


