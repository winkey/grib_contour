
www = @WWW@
wwwdisk = @WWWDISK@

bin_SCRIPTS = \
	generic.sh \
	generic2.sh \
	gfs.sh \
	sst.sh \
	gfs2.sh \
	nam_west.sh \
	nam_east.sh \
	nam_hi.sh \
	nam_ak.sh \
	nam_pr.sh \
	nam2.sh \
	makekey.sh \
	forecaster.sh \
	ruc2.sh \
	rtma_ak.sh \
	rtma_conus.sh \
	nogaps.sh \
	ww.sh \
	ecmwf.sh \
	ukmet.sh

    

CLEANFILES = $(bin_SCRIPTS)

EXTRA_DIST = \
	generic.in \
	generic2.in \
	gfs.in \
	sst.in \
	gfs2.in \
	nam_west.in \
	nam_east.in \
	nam_hi.in \
	nam_ak.in \
	nam_pr.in \
	nam2.in \
	makekey.in \
	forecaster.in \
	ruc2.in \
	rtma_ak.in \
	rtma_conus.in \
	nogaps.in \
	ww.in \
	ecmwf.in \
	ukmet.in





dist_bin_SCRIPTS = \
	generic.sh \
	generic2.sh \
	gfs.sh \
	sst.sh \
	gfs2.sh \
	nam_west.sh \
	nam_east.sh \
	nam_hi.sh \
	nam_ak.sh \
	nam_pr.sh \
	nam2.sh \
	makekey.sh \
	forecaster.sh \
	ruc2.sh \
	rtma_ak.sh \
	rtma_conus.sh \
	ww.sh \
	nogaps.sh \
	ecmwf.sh \
	ukmet.sh 


   
do_subst = sed -e 's,[@]bindir[@],$(bindir),g' \
							 -e 's,[@]wwwdisk[@],$(wwwdisk),g' \
							 -e 's,[@]www[@],$(www),g'
     
generic.sh: generic.in Makefile
	$(do_subst) < $(srcdir)/generic.in > generic.sh
	chmod +x generic.sh

generic2.sh: generic4.in Makefile
	$(do_subst) < $(srcdir)/generic4.in > generic2.sh
	chmod +x generic2.sh

gfs.sh: gfs.in Makefile
	$(do_subst) < $(srcdir)/gfs.in > gfs.sh
	chmod +x gfs.sh

sst.sh: sst.in Makefile
	$(do_subst) < $(srcdir)/sst.in > sst.sh
	chmod +x sst.sh

gfs2.sh: gfs2.in Makefile
	$(do_subst) < $(srcdir)/gfs2.in > gfs2.sh
	chmod +x gfs2.sh

nam_west.sh: nam_west.in Makefile
	$(do_subst) < $(srcdir)/nam_west.in > nam_west.sh
	chmod +x nam_west.sh

nam_east.sh: nam_east.in Makefile
	$(do_subst) < $(srcdir)/nam_east.in > nam_east.sh
	chmod +x nam_east.sh

nam_pr.sh: nam_pr.in Makefile
	$(do_subst) < $(srcdir)/nam_pr.in > nam_pr.sh
	chmod +x nam_pr.sh

nam_hi.sh: nam_hi.in Makefile
	$(do_subst) < $(srcdir)/nam_hi.in > nam_hi.sh
	chmod +x nam_hi.sh

nam_ak.sh: nam_ak.in Makefile
	$(do_subst) < $(srcdir)/nam_ak.in > nam_ak.sh
	chmod +x nam_ak.sh

nam2.sh: nam2.in Makefile
	$(do_subst) < $(srcdir)/nam2.in > nam2.sh
	chmod +x nam2.sh

ruc2.sh: ruc2.in Makefile
	$(do_subst) < $(srcdir)/ruc2.in > ruc2.sh
	chmod +x ruc2.sh

forecaster.sh: forecaster.in Makefile
	$(do_subst) < $(srcdir)/forecaster.in > forecaster.sh
	chmod +x forecaster.sh

makekey.sh: makekey.in Makefile
	$(do_subst) < $(srcdir)/makekey.in > makekey.sh
	chmod +x makekey.sh

rtma_ak.sh: rtma_ak.in Makefile
	$(do_subst) < $(srcdir)/rtma_ak.in > rtma_ak.sh
	chmod +x rtma_ak.sh

rtma_conus.sh: rtma_conus.in Makefile
	$(do_subst) < $(srcdir)/rtma_conus.in > rtma_conus.sh
	chmod +x rtma_conus.sh

ww.sh: ww.in Makefile
	$(do_subst) < $(srcdir)/ww.in > ww.sh
	chmod +x ww.sh

nogaps.sh: nogaps.in Makefile
	$(do_subst) < $(srcdir)/nogaps.in > nogaps.sh
	chmod +x nogaps.sh

ecmwf.sh: ecmwf.in Makefile
	$(do_subst) < $(srcdir)/ecmwf.in > ecmwf.sh
	chmod +x ecmwf.sh

ukmet.sh: ukmet.in Makefile
	$(do_subst) < $(srcdir)/ukmet.in > ukmet.sh
	chmod +x ukmet.sh


