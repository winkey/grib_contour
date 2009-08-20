INCLUDES = \
	$(DEPS_CFLAGS) \
	$(GDAL_CFLAGS)

LIBS = \
	$(DEPS_LIBS) \
	$(GDAL_LIBS)


www = @WWW@
wwwdisk = @WWWDISK@

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	-DPACKAGE_PKG_DATA_DIR=\""$(pkgdatadir)"\" \
	-DPACKAGE_WWW=\""$(www)/kml"\"
	
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
	gribdump.h        \
	style.c        \
	style.h        \
	hilo.c        \
	hilo.h


grib_contour_LDADD = 


