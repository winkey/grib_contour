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
	sst-latest.kml \
	windwave.kml \
	windwave-latest.kml \
	nogaps.kml \
	nogaps-latest.kml \
	ocean.kml \
	ocean-latest.kml \
	ww3.kml \
	ww3-latest.kml \
	coamps_cent_am.kml \
	coamps_cent_am-latest.kml \
	coamps_e_pac.kml \
	coamps_e_pac-latest.kml \
	coamps_w_atl.kml \
	coamps_w_atl-latest.kml \
	coamps_europe.kml \
	coamps_europe-latest.kml \
	ecmwf.kml \
	ecmwf-latest.kml \
	ukmet.kml \
	ukmet-latest.kml

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

rtma_conus.kml: ../scripts/mkkml_nolevel.sh ../share/rtma_conus.config.sh Makefile
	../scripts/mkkml_nolevel.sh ../share/rtma_conus.config.sh
	
rtma_conus-latest.kml: ../scripts/mkkml_nolevel-latest.sh ../share/rtma_conus.config.sh Makefile
	../scripts/mkkml_nolevel-latest.sh ../share/rtma_conus.config.sh

rtma_ak.kml: ../scripts/mkkml_nolevel.sh ../share/rtma_ak.config.sh Makefile
	../scripts/mkkml_nolevel.sh ../share/rtma_ak.config.sh
	
rtma_ak-latest.kml: ../scripts/mkkml_nolevel-latest.sh ../share/rtma_ak.config.sh Makefile
	../scripts/mkkml_nolevel-latest.sh ../share/rtma_ak.config.sh

windwave.kml: ../scripts/mkkml_nolevel.sh ../share/windwave.config.sh Makefile
	../scripts/mkkml_nolevel.sh ../share/windwave.config.sh
	
windwave-latest.kml: ../scripts/mkkml_nolevel-latest.sh ../share/windwave.config.sh Makefile
	../scripts/mkkml_nolevel-latest.sh ../share/windwave.config.sh

nogaps.kml: ../scripts/mkkml.sh ../share/nogaps.config.sh Makefile
	../scripts/mkkml.sh ../share/nogaps.config.sh
	
nogaps-latest.kml: ../scripts/mkkml-latest.sh ../share/nogaps.config.sh Makefile
	../scripts/mkkml-latest.sh ../share/nogaps.config.sh

ocean.kml: ../scripts/mkkml_nolevel.sh ../share/ocean.config.sh Makefile
	../scripts/mkkml_nolevel.sh ../share/ocean.config.sh
	
ocean-latest.kml: ../scripts/mkkml_nolevel-latest.sh ../share/ocean.config.sh Makefile
	../scripts/mkkml_nolevel-latest.sh ../share/ocean.config.sh

ww3.kml: ../scripts/mkkml_nolevel.sh ../share/ww3.config.sh Makefile
	../scripts/mkkml_nolevel.sh ../share/ww3.config.sh
	
ww3-latest.kml: ../scripts/mkkml_nolevel-latest.sh ../share/ww3.config.sh Makefile
	../scripts/mkkml_nolevel-latest.sh ../share/ww3.config.sh

coamps_cent_am.kml: ../scripts/mkkml.sh ../share/coamps_cent_am.config.sh Makefile
	../scripts/mkkml.sh ../share/coamps_cent_am.config.sh
	
coamps_cent_am-latest.kml: ../scripts/mkkml-latest.sh ../share/coamps_cent_am.config.sh Makefile
	../scripts/mkkml-latest.sh ../share/coamps_cent_am.config.sh

coamps_e_pac.kml: ../scripts/mkkml.sh ../share/coamps_e_pac.config.sh Makefile
	../scripts/mkkml.sh ../share/coamps_e_pac.config.sh
	
coamps_e_pac-latest.kml: ../scripts/mkkml-latest.sh ../share/coamps_e_pac.config.sh Makefile
	../scripts/mkkml-latest.sh ../share/coamps_e_pac.config.sh

coamps_w_atl.kml: ../scripts/mkkml.sh ../share/coamps_w_atl.config.sh Makefile
	../scripts/mkkml.sh ../share/coamps_w_atl.config.sh
	
coamps_w_atl-latest.kml: ../scripts/mkkml-latest.sh ../share/coamps_w_atl.config.sh Makefile
	../scripts/mkkml-latest.sh ../share/coamps_w_atl.config.sh

coamps_europe.kml: ../scripts/mkkml.sh ../share/coamps_europe.config.sh Makefile
	../scripts/mkkml.sh ../share/coamps_europe.config.sh
	
coamps_europe-latest.kml: ../scripts/mkkml-latest.sh ../share/coamps_europe.config.sh Makefile
	../scripts/mkkml-latest.sh ../share/coamps_europe.config.sh

ecmwf.kml: ../scripts/mkkml.sh ../share/ecmwf.config.sh Makefile
	../scripts/mkkml.sh ../share/ecmwf.config.sh
	
ecmwf-latest.kml: ../scripts/mkkml-latest.sh ../share/ecmwf.config.sh Makefile
	../scripts/mkkml-latest.sh ../share/ecmwf.config.sh

ukmet.kml: ../scripts/mkkml.sh ../share/ukmet.config.sh Makefile
	../scripts/mkkml.sh ../share/ukmet.config.sh
	
ukmet-latest.kml: ../scripts/mkkml-latest.sh ../share/ukmet.config.sh Makefile
	../scripts/mkkml-latest.sh ../share/ukmet.config.sh

master.kml: ../scripts/mkmaster.sh Makefile
	../scripts/mkmaster.sh > master.kml

latest.kml: ../scripts/mklatest.sh Makefile
	../scripts/mklatest.sh > latest.kml







## File created by the gnome-build tools


