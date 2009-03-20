
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
	ww.sh \
	ecmwf.sh \
	mkkml.sh \
	mkpage.sh \
	mkkml-latest.sh \
	mkscreenshot.sh \
	mkkml_nolevel.sh \
	mkpage_nolevel.sh \
	mkkml_nolevel-latest.sh \
	mkscreenshot_nolevel.sh

    

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
	ww.in \
	ecmwf.in \
	mkkml.in \
	mkpage.in \
	mkkml-latest.in \
	mkscreenshot.in \
	mkkml_nolevel.in \
	mkpage_nolevel.in \
	mkkml_nolevel-latest.in \
	mkscreenshot_nolevel.in





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
	ecmwf.sh \
	mkkml.sh \
	mkpage.sh \
	mkkml-latest.sh \
	mkscreenshot.sh \
	mkkml_nolevel.sh \
	mkpage_nolevel.sh \
	mkkml_nolevel-latest.sh \
	mkscreenshot_nolevel.sh



   
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

ecmwf.sh: ecmwf.in Makefile
	$(do_subst) < $(srcdir)/ecmwf.in > ecmwf.sh
	chmod +x ecmwf.sh

mkkml.sh: mkkml.in Makefile
	$(do_subst) < $(srcdir)/mkkml.in > mkkml.sh
	chmod +x mkkml.sh

mkpage.sh: mkpage.in Makefile
	$(do_subst) < $(srcdir)/mkpage.in > mkpage.sh
	chmod +x mkpage.sh

mkkml-latest.sh: mkkml-latest.in Makefile
	$(do_subst) < $(srcdir)/mkkml-latest.in > mkkml-latest.sh
	chmod +x mkkml-latest.sh

mkscreenshot.sh: mkscreenshot.in
	$(do_subst) < $(srcdir)/mkscreenshot.in > mkscreenshot.sh
	chmod +x mkscreenshot.sh

mkkml_nolevel.sh: mkkml_nolevel.in Makefile
	$(do_subst) < $(srcdir)/mkkml_nolevel.in > mkkml_nolevel.sh
	chmod +x mkkml_nolevel.sh

mkpage_nolevel.sh: mkpage_nolevel.in Makefile
	$(do_subst) < $(srcdir)/mkpage_nolevel.in > mkpage_nolevel.sh
	chmod +x mkpage_nolevel.sh

mkkml_nolevel-latest.sh: mkkml_nolevel-latest.in Makefile
	$(do_subst) < $(srcdir)/mkkml_nolevel-latest.in > mkkml_nolevel-latest.sh
	chmod +x mkkml_nolevel-latest.sh

mkscreenshot_nolevel.sh: mkscreenshot_nolevel.in
	$(do_subst) < $(srcdir)/mkscreenshot_nolevel.in > mkscreenshot_nolevel.sh
	chmod +x mkscreenshot_nolevel.sh

## File created by the gnome-build tools
