## File created by the gnome-build tools


www = @WWW@
wwwdisk = @WWWDISK@

wwwdir = ${wwwdisk}/kml/screenshot

EXTRA_DIST = \
$(shell source ../share/gfs.config.sh ;        echo "$$screenshots" ; echo "$$thumbs") \
$(shell source ../share/nam_conus.config.sh ;  echo "$$screenshots" ; echo "$$thumbs") 
#$(shell source ../share/nam_east.config.sh ;   echo "$$screenshots" ; echo "$$thumbs") \
#$(shell source ../share/nam_west.config.sh ;   echo "$$screenshots" ; echo "$$thumbs") \
#$(shell source ../share/nam_ak.config.sh ;     echo "$$screenshots" ; echo "$$thumbs") \
#$(shell source ../share/ruc2.config.sh ;       echo "$$screenshots" ; echo "$$thumbs") \
#$(shell source ../share/forecaster.config.sh ; echo "$$screenshots" ; echo "$$thumbs") \
#$(shell source ../share/sst.config.sh ;        echo "$$screenshots" ; echo "$$thumbs") \
#$(shell source ../share/windwave.config.sh ;   echo "$$screenshots" ; echo "$$thumbs") \
#$(shell source ../share/nogaps.config.sh ;     echo "$$screenshots" ; echo "$$thumbs") \
#$(shell source ../share/ocean.config.sh ;      echo "$$screenshots" ; echo "$$thumbs") \
#$(shell source ../share/ww3.config.sh ;        echo "$$screenshots" ; echo "$$thumbs") \
#$(shell source ../share/coamps_cent_am.config.sh ; echo "$$screenshots" ; echo "$$thumbs") \
#$(shell source ../share/coamps_e_pac.config.sh ;   echo "$$screenshots" ; echo "$$thumbs") \
#$(shell source ../share/coamps_europe.config.sh ;  echo "$$screenshots" ; echo "$$thumbs") \
#$(shell source ../share/ecmwf.config.sh ;      echo "$$screenshots" ; echo "$$thumbs") \
#$(shell source ../share/ukmet.config.sh ;      echo "$$screenshots" ; echo "$$thumbs")

www_DATA := \
$(shell source ../share/gfs.config.sh ;        echo "$$screenshots" ; echo "$$thumbs") \
$(shell source ../share/nam_conus.config.sh ;  echo "$$screenshots" ; echo "$$thumbs") 
#$(shell source ../share/nam_east.config.sh ;   echo "$$screenshots" ; echo "$$thumbs") \
#$(shell source ../share/nam_west.config.sh ;   echo "$$screenshots" ; echo "$$thumbs") \
#$(shell source ../share/nam_ak.config.sh ;     echo "$$screenshots" ; echo "$$thumbs") \
#$(shell source ../share/ruc2.config.sh ;       echo "$$screenshots" ; echo "$$thumbs") \
#$(shell source ../share/forecaster.config.sh ; echo "$$screenshots" ; echo "$$thumbs") \
#$(shell source ../share/sst.config.sh ;        echo "$$screenshots" ; echo "$$thumbs") \
#$(shell source ../share/windwave.config.sh ;   echo "$$screenshots" ; echo "$$thumbs") \
#$(shell source ../share/nogaps.config.sh ;     echo "$$screenshots" ; echo "$$thumbs") \
#$(shell source ../share/ocean.config.sh ;      echo "$$screenshots" ; echo "$$thumbs") \
#$(shell source ../share/ww3.config.sh ;        echo "$$screenshots" ; echo "$$thumbs") \
#$(shell source ../share/coamps_cent_am.config.sh ; echo "$$screenshots" ; echo "$$thumbs") \
#$(shell source ../share/coamps_e_pac.config.sh ;   echo "$$screenshots" ; echo "$$thumbs") \
#$(shell source ../share/coamps_europe.config.sh ;  echo "$$screenshots" ; echo "$$thumbs") \
#$(shell source ../share/ecmwf.config.sh ;      echo "$$screenshots" ; echo "$$thumbs") \
#$(shell source ../share/ukmet.config.sh ;      echo "$$screenshots" ; echo "$$thumbs")



MAINTAINERCLEANFILES = $(EXTRA_DIST)

gfs_%.jpg: ../scripts/mkscreenshot.sh
	@echo $(www_DATA)
	../scripts/mkscreenshot.sh ../share/gfs.config.sh

nam_conus_%.jpg: 
	../scripts/mkscreenshot.sh ../share/nam_conus.config.sh

nam_east_%.jpg: 
	../scripts/mkscreenshot.sh ../share/nam_east.config.sh

nam_west_%.jpg: 
	../scripts/mkscreenshot.sh ../share/nam_west.config.sh

nam_ak_%.jpg: 
	../scripts/mkscreenshot.sh ../share/nam_ak.config.sh

ruc2_%.jpg: ../scripts/mkscreenshot.sh
	../scripts/mkscreenshot.sh ../share/ruc2.config.sh

forecaster_%.jpg: ../scripts/mkscreenshot_nolevel.sh
	../scripts/mkscreenshot_nolevel.sh ../share/forecaster.config.sh

sst_%.jpg: ../scripts/mkscreenshot_nolevel.sh
	../scripts/mkscreenshot_nolevel.sh ../share/sst.config.sh

rtma_conus_%.jpg: ../scripts/mkscreenshot_nolevel.sh
	../scripts/mkscreenshot_nolevel.sh ../share/rtma_conus.config.sh

rtma_ak_%.jpg: ../scripts/mkscreenshot_nolevel.sh
	../scripts/mkscreenshot_nolevel.sh ../share/rtma_ak.config.sh

windwave_%.jpg: ../scripts/mkscreenshot_nolevel.sh
	../scripts/mkscreenshot_nolevel.sh ../share/windwave.config.sh

nogaps_%.jpg: ../scripts/mkscreenshot.sh
	../scripts/mkscreenshot.sh ../share/nogaps.config.sh

ocean_%.jpg: ../scripts/mkscreenshot.sh
	../scripts/mkscreenshot_nolevel.sh ../share/ocean.config.sh

ww3_%.jpg: ../scripts/mkscreenshot.sh
	../scripts/mkscreenshot_nolevel.sh ../share/ww3.config.sh

coamps_cent_am_%.jpg: ../scripts/mkscreenshot.sh
	../scripts/mkscreenshot.sh ../share/coamps_cent_am.config.sh

coamps_e_pac_%.jpg: ../scripts/mkscreenshot.sh
	../scripts/mkscreenshot.sh ../share/coamps_e_pac.config.sh

coamps_europe_%.jpg: ../scripts/mkscreenshot.sh
	../scripts/mkscreenshot.sh ../share/coamps_europe.config.sh

ecmwf_%.jpg: ../scripts/mkscreenshot.sh
	../scripts/mkscreenshot.sh ../share/ecmwf.config.sh

ukmet_%.jpg: ../scripts/mkscreenshot.sh
	../scripts/mkscreenshot.sh ../share/ukmet.config.sh

%.png: %.jpg
	convert $< -resize 198x159 $@


