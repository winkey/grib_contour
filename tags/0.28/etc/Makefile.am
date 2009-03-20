## File created by the gnome-build tools


sysconf_DATA = \
	pqact.grib_contour.conf

CLEANFILES = $(sysconf_DATA)

EXTRA_DIST = \
	pqact.grib_contour.conf.in

do_subst = sed -e 's,[@]bindir[@],$(bindir),g'

pqact.grib_contour.conf: pqact.grib_contour.conf.in Makefile
	$(do_subst) < $(srcdir)/pqact.grib_contour.conf.in > pqact.grib_contour.conf

