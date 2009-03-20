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
	color.c        \
	color.h        \
	options.c        \
	options.h        \
	contour.c        \
	contour.h        \
	merge.c        \
	merge.h        \
	gribdump.c        \
	gribdump.h

grib_contour_LDFLAGS =          \
	-lgdal          \
	-lzip          \
	-lweathercalc          \
	-lKML



grib_contour_LDADD = 


