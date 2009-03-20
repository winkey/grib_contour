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
	master.kml.in \
	latest.kml.in \
	rtma_conus.kml.in \
	rtma_conus-latest.kml.in \
	rtma_ak.kml.in \
	rtma_ak-latest.kml.in \
	ecmwf.kml.in \
	ecmwf-latest.kml.in
	
do_subst = sed -e 's,[@]bindir[@],$(bindir),g' \
							 -e 's,[@]wwwdisk[@],$(wwwdisk),g' \
							 -e 's,[@]www[@],$(www),g'

gfs.kml: ../scripts/mkkml.sh ../share/gfs.config.sh Makefile
	../scripts/mkkml.sh ../share/gfs.config.sh
	
gfs-latest.kml: ../scripts/mkkml-latest.sh ../share/gfs.config.sh Makefile
	../scripts/mkkml-latest.sh ../share/gfs.config.sh
	
nam_conus.kml: ../scripts/mkkml.sh ../share/nam_conus.config.sh Makefile
	../scripts/mkkml.sh ../share/nam_conus.config.sh

nam_conus-latest.kml: ../scripts/mkkml-latest.sh ../share/nam_conus.config.sh Makefile
	../scripts/mkkml-latest.sh ../share/nam_conus.config.sh

nam_ak.kml: ../scripts/mkkml.sh ../share/nam_ak.config.sh Makefile
	../scripts/mkkml.sh ../share/nam_ak.config.sh

nam_ak-latest.kml: ../scripts/mkkml-latest.sh ../share/nam_ak.config.sh Makefile
	../scripts/mkkml-latest.sh ../share/nam_ak.config.sh

nam_east.kml: ../scripts/mkkml.sh ../share/nam_east.config.sh Makefile
	../scripts/mkkml.sh ../share/nam_east.config.sh

nam_east-latest.kml: ../scripts/mkkml-latest.sh ../share/nam_east.config.sh Makefile
	../scripts/mkkml-latest.sh ../share/nam_east.config.sh

nam_hi.kml: ../scripts/mkkml.sh ../share/nam_hi.config.sh Makefile
	../scripts/mkkml.sh ../share/nam_hi.config.sh

nam_hi-latest.kml: ../scripts/mkkml-latest.sh ../share/nam_hi.config.sh Makefile
	../scripts/mkkml-latest.sh ../share/nam_hi.config.sh

nam_pr.kml: ../scripts/mkkml.sh ../share/nam_pr.config.sh Makefile
	../scripts/mkkml.sh ../share/nam_pr.config.sh

nam_pr-latest.kml: ../scripts/mkkml-latest.sh ../share/nam_pr.config.sh Makefile
	../scripts/mkkml-latest.sh ../share/nam_pr.config.sh

nam_west.kml: ../scripts/mkkml.sh ../share/nam_west.config.sh Makefile
	../scripts/mkkml.sh ../share/nam_west.config.sh

nam_west-latest.kml: ../scripts/mkkml-latest.sh ../share/nam_west.config.sh Makefile
	../scripts/mkkml-latest.sh ../share/nam_west.config.sh

ruc2.kml: ../scripts/mkkml.sh ../share/ruc2.config.sh Makefile
	../scripts/mkkml.sh ../share/ruc2.config.sh
	
ruc2-latest.kml: ../scripts/mkkml-latest.sh ../share/ruc2.config.sh Makefile
	../scripts/mkkml-latest.sh ../share/ruc2.config.sh

forecaster.kml: ../scripts/mkkml_nolevel.sh ../share/forecaster.config.sh Makefile
	../scripts/mkkml_nolevel.sh ../share/forecaster.config.sh
	
forecaster-latest.kml: ../scripts/mkkml_nolevel-latest.sh ../share/forecaster.config.sh Makefile
	../scripts/mkkml_nolevel-latest.sh ../share/forecaster.config.sh

sst.kml: ../scripts/mkkml_nolevel.sh ../share/sst.config.sh Makefile
	../scripts/mkkml_nolevel.sh ../share/sst.config.sh
	
sst-latest.kml: ../scripts/mkkml_nolevel-latest.sh ../share/sst.config.sh Makefile
	../scripts/mkkml_nolevel-latest.sh ../share/sst.config.sh

windwave.kml: ../scripts/mkkml_nolevel.sh ../share/windwave.config.sh Makefile
	../scripts/mkkml_nolevel.sh ../share/windwave.config.sh
	
windwave-latest.kml: ../scripts/mkkml_nolevel-latest.sh ../share/windwave.config.sh Makefile
	../scripts/mkkml_nolevel-latest.sh ../share/windwave.config.sh

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

ecmwf.kml: ecmwf.kml.in Makefile
	$(do_subst) < $(srcdir)/ecmwf.kml.in > ecmwf.kml

ecmwf-latest.kml: ecmwf-latest.kml.in Makefile
	$(do_subst) < $(srcdir)/ecmwf-latest.kml.in > ecmwf-latest.kml


## File created by the gnome-build tools


