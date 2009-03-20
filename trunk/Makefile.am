## Process this file with automake to produce Makefile.in
## Created by Anjuta

www = @WWW@
wwwdisk = @WWWDISK@

SUBDIRS = src \
	scripts\
	share \
	images

grib_contourdocdir = ${prefix}/doc/grib_contour
grib_contourdoc_DATA = \
	README\
	COPYING\
	AUTHORS\
	ChangeLog\
	INSTALL\
	NEWS

EXTRA_DIST = $(grib_contourdoc_DATA)

# Copy all the spec files. Of cource, only one is actually used.
dist-hook:
	for specfile in *.spec; do \
		if test -f $$specfile; then \
			cp -p $$specfile $(distdir); \
		fi \
	done

