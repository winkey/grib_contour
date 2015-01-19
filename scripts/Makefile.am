
www = @WWW@
wwwdisk = @WWWDISK@

bin_SCRIPTS = \
	kml.bash \
	generic2.sh \
	generic_contour.sh \
	scour_contour.sh \
	sst.sh \
	makekey.sh \
	mkkml.sh \
	mkmaster.sh \
	NewWorld.bash \
	mknewworld.sh \
	mkkml_nolevel.sh \
	checkpqact.conf.sh \
	rtma_ak.sh \
	rtma_conus.sh \
	ww.sh \
	ecmwf.sh \
	ukmet.sh

    

CLEANFILES = $(bin_SCRIPTS)

EXTRA_DIST = \
	kml.bash.in \
	generic2.in \
	generic_contour.in \
	scour_contour.in \
	sst.in \
	makekey.in \
	mkkml.in \
	mkmaster.in \
	NewWorld.bash.in \
	mknewworld.in \
	mkkml_nolevel.in \
	rtma_ak.in \
	rtma_conus.in \
	ww.in \
	ecmwf.in \
	ukmet.in





dist_bin_SCRIPTS = \
	kml.bash \
	generic2.sh \
	generic_contour.sh \
	scour_contour.sh \
	sst.sh \
	makekey.sh \
	mkkml.sh \
	mkmaster.sh \
	NewWorld.bash \
	mknewworld.sh \
	mkkml_nolevel.sh \
	checkpqact.conf.sh \
	rtma_ak.sh \
	rtma_conus.sh \
	ww.sh \
	ecmwf.sh \
	ukmet.sh 


   
do_subst = sed -e 's,[@]bindir[@],$(bindir),g' \
               -e 's,[@]PKGDATADIR[@],$(pkgdatadir),g' \
               -e 's,[@]wwwdisk[@],$(wwwdisk),g' \
               -e 's,[@]www[@],$(www),g'
     
kml.bash: kml.bash.in Makefile
	$(do_subst) < $(srcdir)/kml.bash.in > kml.bash
	chmod +x kml.bash

generic2.sh: generic2.in Makefile
	$(do_subst) < $(srcdir)/generic2.in > generic2.sh
	chmod +x generic2.sh

generic_contour.sh: generic_contour.in Makefile
	$(do_subst) < $(srcdir)/generic_contour.in > generic_contour.sh
	chmod +x generic_contour.sh

scour_contour.sh: scour_contour.in Makefile
	$(do_subst) < $(srcdir)/scour_contour.in > scour_contour.sh
	chmod +x scour_contour.sh

sst.sh: sst.in Makefile
	$(do_subst) < $(srcdir)/sst.in > sst.sh
	chmod +x sst.sh

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

NewWorld.bash: NewWorld.bash.in Makefile
	$(do_subst) < $(srcdir)/NewWorld.bash.in > NewWorld.bash
	chmod +x NewWorld.bash

mknewworld.sh: mknewworld.in Makefile
	$(do_subst) < $(srcdir)/mknewworld.in > mknewworld.sh
	chmod +x mknewworld.sh

mkkml_nolevel.sh: mkkml_nolevel.in Makefile
	$(do_subst) < $(srcdir)/mkkml_nolevel.in > mkkml_nolevel.sh
	chmod +x mkkml_nolevel.sh


