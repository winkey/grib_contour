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

bin_PROGRAMS = \
	grib_contour

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
	kml.h        \
	options.c        \
	options.h        \
	contour.c        \
	contour.h

grib_contour_LDFLAGS = \
	-lgdal          \
	-lzip          \
	-lweathercalc



grib_contour_LDADD = 


