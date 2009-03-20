## File created by the gnome-build tools


www = @WWW@
wwwdisk = @WWWDISK@

wwwdir = ${wwwdisk}/kml/screenshot

EXTRA_DIST = \
$(shell source ../share/gfs.config.sh ;        echo "$$screenshots" ; echo "$$thumbs") \
$(shell source ../share/nam_conus.config.sh ;  echo "$$screenshots" ; echo "$$thumbs") \
$(shell source ../share/ruc2.config.sh ;       echo "$$screenshots" ; echo "$$thumbs") \
$(shell source ../share/forecaster.config.sh ; echo "$$screenshots" ; echo "$$thumbs") \
$(shell source ../share/sst.config.sh ;        echo "$$screenshots" ; echo "$$thumbs") \
$(shell source ../share/windwave.config.sh ;   echo "$$screenshots" ; echo "$$thumbs")

www_DATA := \
$(shell source ../share/gfs.config.sh ;        echo "$$screenshots" ; echo "$$thumbs") \
$(shell source ../share/nam_conus.config.sh ;  echo "$$screenshots" ; echo "$$thumbs") \
$(shell source ../share/ruc2.config.sh ;       echo "$$screenshots" ; echo "$$thumbs") \
$(shell source ../share/forecaster.config.sh ; echo "$$screenshots" ; echo "$$thumbs") \
$(shell source ../share/sst.config.sh ;        echo "$$screenshots" ; echo "$$thumbs") \
$(shell source ../share/windwave.config.sh ;   echo "$$screenshots" ; echo "$$thumbs")

gfs_%.jpg: ../scripts/mkscreenshot.sh
	@echo $(www_DATA)
	../scripts/mkscreenshot.sh ../share/gfs.config.sh

nam_conus_%.jpg: 
	../scripts/mkscreenshot.sh ../share/nam_conus.config.sh

ruc2_%.jpg: ../scripts/mkscreenshot.sh
	../scripts/mkscreenshot.sh ../share/ruc2.config.sh

forecaster_%.jpg: ../scripts/mkscreenshot.sh
	../scripts/mkscreenshot_nolevel.sh ../share/forecaster.config.sh

sst_%.jpg: ../scripts/mkscreenshot.sh
	../scripts/mkscreenshot_nolevel.sh ../share/sst.config.sh

windwave_%.jpg: ../scripts/mkscreenshot.sh
	../scripts/mkscreenshot_nolevel.sh ../share/windwave.config.sh

%.png: %.jpg
	convert $< -resize 198x159 $@
