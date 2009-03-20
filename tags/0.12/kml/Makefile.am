www = @WWW@
wwwdisk = @WWWDISK@

wwwdir = ${wwwdisk}/kml

www_DATA = \
	gfs.kml \
	nam_conus.kml \
	ruc2.kml \
	forecaster.kml \
	nam_ak.kml \
	nam_east.kml \
	nam_hi.kml \
	nam_pr.kml \
	nam_west.kml \
	master.kml \
	rtma_conus.kml \
	rtma_ak.kml \
	sst.kml

EXTRA_DIST = \
	gfs.kml.in \
	nam_conus.kml.in \
	ruc2.kml.in \
	forecaster.kml.in \
	nam_ak.kml.in \
	nam_east.kml.in \
	nam_hi.kml.in \
	nam_pr.kml.in \
	nam_west.kml.in \
	master.kml.in \
	rtma_conus.kml.in \
	rtma_ak.kml.in \
	sst.kml.in
	
do_subst = sed -e 's,[@]bindir[@],$(bindir),g' \
							 -e 's,[@]wwwdisk[@],$(wwwdisk),g' \
							 -e 's,[@]www[@],$(www),g'
     
gfs.kml: gfs.kml.in Makefile
	$(do_subst) < $(srcdir)/gfs.kml.in > gfs.kml
	chmod +x gfs.kml

nam_conus.kml: nam_conus.kml.in Makefile
	$(do_subst) < $(srcdir)/nam_conus.kml.in > nam_conus.kml

ruc2.kml: ruc2.kml.in Makefile
	$(do_subst) < $(srcdir)/ruc2.kml.in > ruc2.kml

forecaster.kml: forecaster.kml.in Makefile
	$(do_subst) < $(srcdir)/forecaster.kml.in > forecaster.kml

nam_ak.kml: nam_ak.kml.in Makefile
	$(do_subst) < $(srcdir)/nam_ak.kml.in > nam_ak.kml
	
nam_east.kml: nam_east.kml.in Makefile
	$(do_subst) < $(srcdir)/nam_east.kml.in > nam_east.kml

nam_hi.kml: nam_hi.kml.in Makefile
	$(do_subst) < $(srcdir)/nam_hi.kml.in > nam_hi.kml

nam_pr.kml: nam_pr.kml.in Makefile
	$(do_subst) < $(srcdir)/nam_pr.kml.in > nam_pr.kml

nam_west.kml: nam_west.kml.in Makefile
	$(do_subst) < $(srcdir)/nam_west.kml.in > nam_west.kml

master.kml: master.kml.in Makefile
	$(do_subst) < $(srcdir)/master.kml.in > master.kml

rtma_conus.kml: rtma_conus.kml.in Makefile
	$(do_subst) < $(srcdir)/rtma_conus.kml.in > rtma_conus.kml

rtma_ak.kml: rtma_ak.kml.in Makefile
	$(do_subst) < $(srcdir)/rtma_ak.kml.in > rtma_ak.kml

sst.kml: sst.kml.in Makefile
	$(do_subst) < $(srcdir)/sst.kml.in > sst.kml


## File created by the gnome-build tools


