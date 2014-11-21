
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
	hrrr.sh \
	makekey.sh \
	mkkml.sh \
	mkmaster.sh \
	mklatest.sh \
	mknewworld.sh \
	mkkml-latest.sh \
	mkkml_nolevel.sh \
	mkkml_nolevel-latest.sh \
	checkpqact.conf.sh \
	forecaster.sh \
	rap.sh \
	rtma_ak.sh \
	rtma_conus.sh \
	navgem.sh \
	coamps_cent_am.sh \
	coamps_ne_pac.sh \
	coamps_w_atl.sh \
	coamps_socal.sh \
	coamps_cencoos.sh \
	ocean.sh \
	ww.sh \
	ww3.sh \
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
	hrrr.in \
	makekey.in \
	mkkml.in \
	mkmaster.in \
	mklatest.in \
	mknewworld.in \
	mkkml-latest.in \
	mkkml_nolevel.in \
	mkkml_nolevel-latest.in \
	forecaster.in \
	rap.in \
	rtma_ak.in \
	rtma_conus.in \
	navgem.in \
	coamps_cent_am.in \
	coamps_ne_pac.in \
	coamps_w_atl.in \
	coamps_socal.in \
	coamps_cencoos.in \
	ocean.in \
	ww.in \
	ww3.in \
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
	hrrr.sh \
	makekey.sh \
	mkkml.sh \
	mkmaster.sh \
	mklatest.sh \
	mknewworld.sh \
	mkkml-latest.sh \
	mkkml_nolevel.sh \
	mkkml_nolevel-latest.sh \
	checkpqact.conf.sh \
	forecaster.sh \
	rap.sh \
	rtma_ak.sh \
	rtma_conus.sh \
	ww.sh \
	ww3.sh \
	navgem.sh \
	coamps_cent_am.sh \
	coamps_ne_pac.sh \
	coamps_w_atl.sh \
	coamps_socal.sh \
	coamps_cencoos.sh \
	ocean.sh \
	ecmwf.sh \
	ukmet.sh 


   
do_subst = sed -e 's,[@]bindir[@],$(bindir),g' \
							 -e 's,[@]wwwdisk[@],$(wwwdisk),g' \
							 -e 's,[@]www[@],$(www),g'
     
generic.sh: generic.in Makefile
	$(do_subst) < $(srcdir)/generic.in > generic.sh
	chmod +x generic.sh

generic2.sh: generic2.in Makefile
	$(do_subst) < $(srcdir)/generic2.in > generic2.sh
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

hrrr.sh: hrrr.in Makefile
	$(do_subst) < $(srcdir)/hrrr.in > hrrr.sh
	chmod +x hrrr.sh

rap.sh: rap.in Makefile
	$(do_subst) < $(srcdir)/rap.in > rap.sh
	chmod +x rap.sh

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

ww3.sh: ww3.in Makefile
	$(do_subst) < $(srcdir)/ww3.in > ww3.sh
	chmod +x ww3.sh

navgem.sh: navgem.in Makefile
	$(do_subst) < $(srcdir)/navgem.in > navgem.sh
	chmod +x navgem.sh

coamps_cent_am.sh: coamps_cent_am.in Makefile
	$(do_subst) < $(srcdir)/coamps_cent_am.in > coamps_cent_am.sh
	chmod +x coamps_cent_am.sh

coamps_ne_pac.sh: coamps_ne_pac.in Makefile
	$(do_subst) < $(srcdir)/coamps_ne_pac.in > coamps_ne_pac.sh
	chmod +x coamps_ne_pac.sh

coamps_w_atl.sh: coamps_w_atl.in Makefile
	$(do_subst) < $(srcdir)/coamps_w_atl.in > coamps_w_atl.sh
	chmod +x coamps_w_atl.sh

coamps_socal.sh: coamps_socal.in Makefile
	$(do_subst) < $(srcdir)/coamps_socal.in > coamps_socal.sh
	chmod +x coamps_socal.sh

coamps_cencoos.sh: coamps_cencoos.in Makefile
	$(do_subst) < $(srcdir)/coamps_cencoos.in > coamps_cencoos.sh
	chmod +x coamps_cencoos.sh

ocean.sh: ocean.in Makefile
	$(do_subst) < $(srcdir)/ocean.in > ocean.sh
	chmod +x ocean.sh

ecmwf.sh: ecmwf.in Makefile
	$(do_subst) < $(srcdir)/ecmwf.in > ecmwf.sh
	chmod +x ecmwf.sh

ukmet.sh: ukmet.in Makefile
	$(do_subst) < $(srcdir)/ukmet.in > ukmet.sh
	chmod +x ukmet.sh

mkkml.sh: mkkml.in Makefile
	$(do_subst) < $(srcdir)/mkkml.in > mkkml.sh
	chmod +x mkkml.sh

mkmaster.sh: mkmaster.in Makefile
	$(do_subst) < $(srcdir)/mkmaster.in > mkmaster.sh
	chmod +x mkmaster.sh

mklatest.sh: mklatest.in Makefile
	$(do_subst) < $(srcdir)/mklatest.in > mklatest.sh
	chmod +x mklatest.sh

mknewworld.sh: mknewworld.in Makefile
	$(do_subst) < $(srcdir)/mknewworld.in > mknewworld.sh
	chmod +x mknewworld.sh

mkkml-latest.sh: mkkml-latest.in Makefile
	$(do_subst) < $(srcdir)/mkkml-latest.in > mkkml-latest.sh
	chmod +x mkkml-latest.sh

mkkml_nolevel.sh: mkkml_nolevel.in Makefile
	$(do_subst) < $(srcdir)/mkkml_nolevel.in > mkkml_nolevel.sh
	chmod +x mkkml_nolevel.sh

mkkml_nolevel-latest.sh: mkkml_nolevel-latest.in Makefile
	$(do_subst) < $(srcdir)/mkkml_nolevel-latest.in > mkkml_nolevel-latest.sh
	chmod +x mkkml_nolevel-latest.sh


