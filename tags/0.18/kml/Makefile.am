www = @WWW@
wwwdisk = @WWWDISK@

wwwdir = ${wwwdisk}/kml

www_DATA = \
	forecaster.kml \
	forecaster-latest.kml \
	gfs.kml \
	gfs-latest.kml \
	nam_conus.kml \
	nam_conus-latest.kml \
	ruc2.kml \
	ruc2-latest.kml \
	nam_ak.kml \
	nam_ak-latest.kml \
	nam_east.kml \
	nam_east-latest.kml \
	nam_hi.kml \
	nam_hi-latest.kml \
	nam_pr.kml \
	nam_pr-latest.kml \
	nam_west.kml \
	nam_west-latest.kml \
	master.kml \
	latest.kml \
	rtma_conus.kml \
	rtma_conus-latest.kml \
	rtma_ak.kml \
	rtma_ak-latest.kml \
	sst.kml \
	windwave.kml \
	windwave-latest.kml \
	ecmwf.kml \
	ecmwf-latest.kml

EXTRA_DIST = \
	forecaster.kml.in \
	forecaster-latest.kml.in \
	gfs.kml.in \
	gfs-latest.kml.in \
	nam_conus.kml.in \
	nam_conus-latest.kml.in \
	ruc2.kml.in \
	ruc2-latest.kml.in \
	nam_ak.kml.in \
	nam_ak-latest.kml.in \
	nam_east.kml.in \
	nam_east-latest.kml.in \
	nam_hi.kml.in \
	nam_hi-latest.kml.in \
	nam_pr.kml.in \
	nam_pr-latest.kml.in \
	nam_west.kml.in \
	nam_west-latest.kml.in \
	master.kml.in \
	latest.kml.in \
	rtma_conus.kml.in \
	rtma_conus-latest.kml.in \
	rtma_ak.kml.in \
	rtma_ak-latest.kml.in \
	sst.kml.in \
	windwave.kml.in \
	windwave-latest.kml.in \
	ecmwf.kml.in \
	ecmwf-latest.kml.in
	
do_subst = sed -e 's,[@]bindir[@],$(bindir),g' \
							 -e 's,[@]wwwdisk[@],$(wwwdisk),g' \
							 -e 's,[@]www[@],$(www),g'
     
forecaster.kml: forecaster.kml.in Makefile
	$(do_subst) < $(srcdir)/forecaster.kml.in > forecaster.kml

forecaster-latest.kml: forecaster-latest.kml.in Makefile
	$(do_subst) < $(srcdir)/forecaster-latest.kml.in > forecaster-latest.kml

gfs.kml: gfs.kml.in Makefile
	$(do_subst) < $(srcdir)/gfs.kml.in > gfs.kml

gfs-latest.kml: gfs-latest.kml.in Makefile
	$(do_subst) < $(srcdir)/gfs-latest.kml.in > gfs-latest.kml

nam_conus.kml: nam_conus.kml.in Makefile
	$(do_subst) < $(srcdir)/nam_conus.kml.in > nam_conus.kml

nam_conus-latest.kml: nam_conus-latest.kml.in Makefile
	$(do_subst) < $(srcdir)/nam_conus-latest.kml.in > nam_conus-latest.kml

ruc2.kml: ruc2.kml.in Makefile
	$(do_subst) < $(srcdir)/ruc2.kml.in > ruc2.kml

ruc2-latest.kml: ruc2-latest.kml.in Makefile
	$(do_subst) < $(srcdir)/ruc2-latest.kml.in > ruc2-latest.kml

nam_ak.kml: nam_ak.kml.in Makefile
	$(do_subst) < $(srcdir)/nam_ak.kml.in > nam_ak.kml
	
nam_ak-latest.kml: nam_ak-latest.kml.in Makefile
	$(do_subst) < $(srcdir)/nam_ak-latest.kml.in > nam_ak-latest.kml
	
nam_east.kml: nam_east.kml.in Makefile
	$(do_subst) < $(srcdir)/nam_east.kml.in > nam_east.kml

nam_east-latest.kml: nam_east-latest.kml.in Makefile
	$(do_subst) < $(srcdir)/nam_east-latest.kml.in > nam_east-latest.kml

nam_hi.kml: nam_hi.kml.in Makefile
	$(do_subst) < $(srcdir)/nam_hi.kml.in > nam_hi.kml

nam_hi-latest.kml: nam_hi-latest.kml.in Makefile
	$(do_subst) < $(srcdir)/nam_hi-latest.kml.in > nam_hi-latest.kml

nam_pr.kml: nam_pr.kml.in Makefile
	$(do_subst) < $(srcdir)/nam_pr.kml.in > nam_pr.kml

nam_pr-latest.kml: nam_pr-latest.kml.in Makefile
	$(do_subst) < $(srcdir)/nam_pr-latest.kml.in > nam_pr-latest.kml

nam_west.kml: nam_west.kml.in Makefile
	$(do_subst) < $(srcdir)/nam_west.kml.in > nam_west.kml

nam_west-latest.kml: nam_west-latest.kml.in Makefile
	$(do_subst) < $(srcdir)/nam_west-latest.kml.in > nam_west-latest.kml

master.kml: master.kml.in Makefile
	$(do_subst) < $(srcdir)/master.kml.in > master.kml

latest.kml: latest.kml.in Makefile
	$(do_subst) < $(srcdir)/latest.kml.in > latest.kml

rtma_conus.kml: rtma_conus.kml.in Makefile
	$(do_subst) < $(srcdir)/rtma_conus.kml.in > rtma_conus.kml

rtma_conus-latest.kml: rtma_conus-latest.kml.in Makefile
	$(do_subst) < $(srcdir)/rtma_conus-latest.kml.in > rtma_conus-latest.kml

rtma_ak.kml: rtma_ak.kml.in Makefile
	$(do_subst) < $(srcdir)/rtma_ak.kml.in > rtma_ak.kml

rtma_ak-latest.kml: rtma_ak-latest.kml.in Makefile
	$(do_subst) < $(srcdir)/rtma_ak-latest.kml.in > rtma_ak-latest.kml

sst.kml: sst.kml.in Makefile
	$(do_subst) < $(srcdir)/sst.kml.in > sst.kml

windwave.kml: windwave.kml.in Makefile
	$(do_subst) < $(srcdir)/windwave.kml.in > windwave.kml

windwave-latest.kml: windwave-latest.kml.in Makefile
	$(do_subst) < $(srcdir)/windwave-latest.kml.in > windwave-latest.kml

ecmwf.kml: ecmwf.kml.in Makefile
	$(do_subst) < $(srcdir)/ecmwf.kml.in > ecmwf.kml

ecmwf-latest.kml: ecmwf-latest.kml.in Makefile
	$(do_subst) < $(srcdir)/ecmwf-latest.kml.in > ecmwf-latest.kml


## File created by the gnome-build tools


