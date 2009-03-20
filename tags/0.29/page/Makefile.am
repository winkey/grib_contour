## File created by the gnome-build tools


www = @WWW@
wwwdisk = @WWWDISK@

wwwdir = ${wwwdisk}/kml/page

EXTRA_DIST = \
	generic.css.in

www_DATA = \
	gfs.php \
	nam_conus.php \
	nam_ak.php \
	nam_east.php \
	nam_hi.php \
	nam_pr.php \
	nam_west.php \
	ruc2.php \
	forecaster.php \
	sst.php \
	windwave.php \
	nogaps.php \
	ecmwf.php \
	gfs.css \
	nam_conus.css \
	nam_ak.css \
	nam_east.css \
	nam_hi.css \
	nam_pr.css \
	nam_west.css \
	ruc2.css \
	forecaster.css \
	sst.css \
	windwave.css \
	nogaps.css \
	ecmwf.css

gfs.php: ../scripts/mkpage.sh ../share/gfs.config.sh Makefile
	../scripts/mkpage.sh ../share/gfs.config.sh

nam_conus.php: ../scripts/mkpage.sh ../share/nam_conus.config.sh Makefile
	../scripts/mkpage.sh ../share/nam_conus.config.sh

nam_ak.php: ../scripts/mkpage.sh ../share/nam_ak.config.sh Makefile
	../scripts/mkpage.sh ../share/nam_ak.config.sh

nam_east.php: ../scripts/mkpage.sh ../share/nam_east.config.sh Makefile
	../scripts/mkpage.sh ../share/nam_east.config.sh

nam_hi.php: ../scripts/mkpage.sh ../share/nam_hi.config.sh Makefile
	../scripts/mkpage.sh ../share/nam_hi.config.sh

nam_pr.php: ../scripts/mkpage.sh ../share/nam_pr.config.sh Makefile
	../scripts/mkpage.sh ../share/nam_pr.config.sh

nam_west.php: ../scripts/mkpage.sh ../share/nam_west.config.sh Makefile
	../scripts/mkpage.sh ../share/nam_west.config.sh

ruc2.php: ../scripts/mkpage.sh ../share/ruc2.config.sh Makefile
	../scripts/mkpage.sh ../share/ruc2.config.sh

forecaster.php: ../scripts/mkpage_nolevel.sh ../share/forecaster.config.sh Makefile
	../scripts/mkpage_nolevel.sh ../share/forecaster.config.sh

sst.php: ../scripts/mkpage_nolevel.sh ../share/sst.config.sh Makefile
	../scripts/mkpage_nolevel.sh ../share/sst.config.sh

windwave.php: ../scripts/mkpage_nolevel.sh ../share/windwave.config.sh Makefile
	../scripts/mkpage_nolevel.sh ../share/windwave.config.sh

nogaps.php: ../scripts/mkpage.sh ../share/nogaps.config.sh Makefile
	../scripts/mkpage.sh ../share/nogaps.config.sh

ecmwf.php: ../scripts/mkpage.sh ../share/ecmwf.config.sh Makefile
	../scripts/mkpage.sh ../share/ecmwf.config.sh

%.css: generic.css.in
	cat generic.css.in > $@
