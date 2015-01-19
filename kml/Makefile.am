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
	hrrr.kml \
	hrrr-latest.kml \
	rap.kml \
	rap-latest.kml \
	nam_ak_hires.kml \
	nam_ak_hires-latest.kml \
	nam_conus_hires.kml \
	nam_conus_hires-latest.kml \
	nam_hi_hires.kml \
	nam_hi_hires-latest.kml \
	nam_pr_hires.kml \
	nam_pr_hires-latest.kml \
	nam_firewx_hires.kml \
	nam_firewx_hires-latest.kml \
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
	navgem.kml \
	navgem-latest.kml \
	ocean.kml \
	ocean-latest.kml \
	ww3.kml \
	ww3-latest.kml \
	coamps_cent_am.kml \
	coamps_cent_am-latest.kml \
	coamps_ne_pac.kml \
	coamps_ne_pac-latest.kml \
	coamps_w_atl.kml \
	coamps_w_atl-latest.kml \
	coamps_cencoos.kml \
	coamps_cencoos-latest.kml \
	coamps_socal.kml \
	coamps_socal-latest.kml \
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

hrrr.kml: ../scripts/mkkml.sh ../share/hrrr.config.sh Makefile
	../scripts/mkkml.sh ../share/hrrr.config.sh

hrrr-latest.kml: ../scripts/mkkml-latest.sh ../share/hrrr.config.sh Makefile
	../scripts/mkkml-latest.sh ../share/hrrr.config.sh

nam_ak_hires.kml: ../scripts/mkkml.sh ../share/nam_ak_hires.config.sh Makefile
	../scripts/mkkml.sh ../share/nam_ak_hires.config.sh

nam_ak_hires-latest.kml: ../scripts/mkkml-latest.sh ../share/nam_ak_hires.config.sh Makefile
	../scripts/mkkml-latest.sh ../share/nam_ak_hires.config.sh

nam_conus_hires.kml: ../scripts/mkkml.sh ../share/nam_conus_hires.config.sh Makefile
	../scripts/mkkml.sh ../share/nam_conus_hires.config.sh

nam_conus_hires-latest.kml: ../scripts/mkkml-latest.sh ../share/nam_conus_hires.config.sh Makefile
	../scripts/mkkml-latest.sh ../share/nam_conus_hires.config.sh

nam_hi_hires.kml: ../scripts/mkkml.sh ../share/nam_hi_hires.config.sh Makefile
	../scripts/mkkml.sh ../share/nam_hi_hires.config.sh

nam_hi_hires-latest.kml: ../scripts/mkkml-latest.sh ../share/nam_hi_hires.config.sh Makefile
	../scripts/mkkml-latest.sh ../share/nam_hi_hires.config.sh

nam_pr_hires.kml: ../scripts/mkkml.sh ../share/nam_pr_hires.config.sh Makefile
	../scripts/mkkml.sh ../share/nam_pr_hires.config.sh

nam_pr_hires-latest.kml: ../scripts/mkkml-latest.sh ../share/nam_pr_hires.config.sh Makefile
	../scripts/mkkml-latest.sh ../share/nam_pr_hires.config.sh

nam_firewx_hires.kml: ../scripts/mkkml.sh ../share/nam_firewx_hires.config.sh Makefile
	../scripts/mkkml.sh ../share/nam_firewx_hires.config.sh

nam_firewx_hires-latest.kml: ../scripts/mkkml-latest.sh ../share/nam_firewx_hires.config.sh Makefile
	../scripts/mkkml-latest.sh ../share/nam_firewx_hires.config.sh

rap.kml: ../scripts/mkkml.sh ../share/rap.config.sh Makefile
	../scripts/mkkml.sh ../share/rap.config.sh
	
rap-latest.kml: ../scripts/mkkml-latest.sh ../share/rap.config.sh Makefile
	../scripts/mkkml-latest.sh ../share/rap.config.sh

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

navgem.kml: ../scripts/mkkml.sh ../share/navgem.config.sh Makefile
	../scripts/mkkml.sh ../share/navgem.config.sh
	
navgem-latest.kml: ../scripts/mkkml-latest.sh ../share/navgem.config.sh Makefile
	../scripts/mkkml-latest.sh ../share/navgem.config.sh

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

coamps_ne_pac.kml: ../scripts/mkkml.sh ../share/coamps_ne_pac.config.sh Makefile
	../scripts/mkkml.sh ../share/coamps_ne_pac.config.sh
	
coamps_ne_pac-latest.kml: ../scripts/mkkml-latest.sh ../share/coamps_ne_pac.config.sh Makefile
	../scripts/mkkml-latest.sh ../share/coamps_ne_pac.config.sh

coamps_w_atl.kml: ../scripts/mkkml.sh ../share/coamps_w_atl.config.sh Makefile
	../scripts/mkkml.sh ../share/coamps_w_atl.config.sh
	
coamps_w_atl-latest.kml: ../scripts/mkkml-latest.sh ../share/coamps_w_atl.config.sh Makefile
	../scripts/mkkml-latest.sh ../share/coamps_w_atl.config.sh

coamps_cencoos.kml: ../scripts/mkkml.sh ../share/coamps_cencoos.config.sh Makefile
	../scripts/mkkml.sh ../share/coamps_cencoos.config.sh
	
coamps_cencoos-latest.kml: ../scripts/mkkml-latest.sh ../share/coamps_cencoos.config.sh Makefile
	../scripts/mkkml-latest.sh ../share/coamps_cencoos.config.sh

coamps_socal.kml: ../scripts/mkkml.sh ../share/coamps_socal.config.sh Makefile
	../scripts/mkkml.sh ../share/coamps_socal.config.sh
	
coamps_socal-latest.kml: ../scripts/mkkml-latest.sh ../share/coamps_socal.config.sh Makefile
	../scripts/mkkml-latest.sh ../share/coamps_socal.config.sh

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
	../scripts/mknewworld.sh

latest.kml: ../scripts/mklatest.sh Makefile
	../scripts/mklatest.sh > latest.kml







## File created by the gnome-build tools


