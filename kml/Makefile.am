www = @WWW@
wwwdisk = @WWWDISK@

wwwdir = ${wwwdisk}/kml

www_DATA = \
	forecaster.kml \
	gfs.kml \
	nam_conus.kml \
	hrrr.kml \
	rap.kml \
	nam_ak_hires.kml \
	nam_conus_hires.kml \
	nam_hi_hires.kml \
	nam_pr_hires.kml \
	nam_firewx_hires.kml \
	master.kml \
	latest.kml \
	rtma_conus.kml \
	rtma_ak.kml \
	sst.kml \
	sst-latest.kml \
	windwave.kml \
	navgem.kml \
	ocean.kml \
	ww3.kml \
	coamps_cent_am.kml \
	coamps_ne_pac.kml \
	coamps_w_atl.kml \
	coamps_cencoos.kml \
	coamps_socal.kml \
	ecmwf.kml \
	ukmet.kml


do_subst = sed -e 's,[@]bindir[@],$(bindir),g' \
							 -e 's,[@]wwwdisk[@],$(wwwdisk),g' \
							 -e 's,[@]www[@],$(www),g'

gfs.kml: ../scripts/mkkml.sh ../share/gfs.config.sh Makefile
	../scripts/mkkml.sh ../share/gfs.config.sh
	
nam_conus.kml: ../scripts/mkkml.sh ../share/nam_conus.config.sh Makefile
	../scripts/mkkml.sh ../share/nam_conus.config.sh

hrrr.kml: ../scripts/mkkml.sh ../share/hrrr.config.sh Makefile
	../scripts/mkkml.sh ../share/hrrr.config.sh

nam_ak_hires.kml: ../scripts/mkkml.sh ../share/nam_ak_hires.config.sh Makefile
	../scripts/mkkml.sh ../share/nam_ak_hires.config.sh

nam_conus_hires.kml: ../scripts/mkkml.sh ../share/nam_conus_hires.config.sh Makefile
	../scripts/mkkml.sh ../share/nam_conus_hires.config.sh

nam_hi_hires.kml: ../scripts/mkkml.sh ../share/nam_hi_hires.config.sh Makefile
	../scripts/mkkml.sh ../share/nam_hi_hires.config.sh

nam_pr_hires.kml: ../scripts/mkkml.sh ../share/nam_pr_hires.config.sh Makefile
	../scripts/mkkml.sh ../share/nam_pr_hires.config.sh

nam_firewx_hires.kml: ../scripts/mkkml.sh ../share/nam_firewx_hires.config.sh Makefile
	../scripts/mkkml.sh ../share/nam_firewx_hires.config.sh

rap.kml: ../scripts/mkkml.sh ../share/rap.config.sh Makefile
	../scripts/mkkml.sh ../share/rap.config.sh
	
forecaster.kml: ../scripts/mkkml_nolevel.sh ../share/forecaster.config.sh Makefile
	../scripts/mkkml_nolevel.sh ../share/forecaster.config.sh
	
sst.kml: ../scripts/mkkml_nolevel.sh ../share/sst.config.sh Makefile
	../scripts/mkkml_nolevel.sh ../share/sst.config.sh
	
rtma_conus.kml: ../scripts/mkkml_nolevel.sh ../share/rtma_conus.config.sh Makefile
	../scripts/mkkml_nolevel.sh ../share/rtma_conus.config.sh
	
rtma_ak.kml: ../scripts/mkkml_nolevel.sh ../share/rtma_ak.config.sh Makefile
	../scripts/mkkml_nolevel.sh ../share/rtma_ak.config.sh
	
windwave.kml: ../scripts/mkkml_nolevel.sh ../share/windwave.config.sh Makefile
	../scripts/mkkml_nolevel.sh ../share/windwave.config.sh
	
navgem.kml: ../scripts/mkkml.sh ../share/navgem.config.sh Makefile
	../scripts/mkkml.sh ../share/navgem.config.sh
	
ocean.kml: ../scripts/mkkml_nolevel.sh ../share/ocean.config.sh Makefile
	../scripts/mkkml_nolevel.sh ../share/ocean.config.sh
	
ww3.kml: ../scripts/mkkml_nolevel.sh ../share/ww3.config.sh Makefile
	../scripts/mkkml_nolevel.sh ../share/ww3.config.sh
	
coamps_cent_am.kml: ../scripts/mkkml.sh ../share/coamps_cent_am.config.sh Makefile
	../scripts/mkkml.sh ../share/coamps_cent_am.config.sh
	
coamps_ne_pac.kml: ../scripts/mkkml.sh ../share/coamps_ne_pac.config.sh Makefile
	../scripts/mkkml.sh ../share/coamps_ne_pac.config.sh
	
coamps_w_atl.kml: ../scripts/mkkml.sh ../share/coamps_w_atl.config.sh Makefile
	../scripts/mkkml.sh ../share/coamps_w_atl.config.sh
	
coamps_cencoos.kml: ../scripts/mkkml.sh ../share/coamps_cencoos.config.sh Makefile
	../scripts/mkkml.sh ../share/coamps_cencoos.config.sh
	
coamps_socal.kml: ../scripts/mkkml.sh ../share/coamps_socal.config.sh Makefile
	../scripts/mkkml.sh ../share/coamps_socal.config.sh
	
ecmwf.kml: ../scripts/mkkml.sh ../share/ecmwf.config.sh Makefile
	../scripts/mkkml.sh ../share/ecmwf.config.sh
	
ukmet.kml: ../scripts/mkkml.sh ../share/ukmet.config.sh Makefile
	../scripts/mkkml.sh ../share/ukmet.config.sh
	

master.kml: ../scripts/mkmaster.sh Makefile
	../scripts/mkmaster.sh > master.kml
	../scripts/mkMapLayers.sh









## File created by the gnome-build tools


