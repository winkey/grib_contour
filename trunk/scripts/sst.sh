# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Library General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor Boston, MA 02110-1301,  USA


source /usr/local/bin/generic.sh

serv="ftp://ftpprd.ncep.noaa.gov/pub/data/nccf/com/gfs/prod/"
servb="http://www.ftp.ncep.noaa.gov/data/nccf/com/gfs/prod/"
wwwdisk="/home/rush/public_html/weather/kml/sst"
www="http://winkey.org/weather/kml/sst"




if [[ ! -d "${wwwdisk}/" ]]
then
	mkdir -p "${wwwdisk}/"
fi

if ! wget "${servb}/sst.${datee}/rtgssthr_grb_0.083_awips.grib2" -O "/tmp/rtgssthr_grb_0.083_awips.grib2"
then
	exit
fi

if [[ -f "${wwwdisk}/sst.kmz" ]]
then
	rm "${wwwdisk}/sst.kmz"
fi

grib_contour -g "/tmp/rtgssthr_grb_0.083_awips.grib2" -m 1 -i .75 -s sst -k sst.kml -z ${wwwdisk}/sst.kmz

rm "${tmp}/${gribfile}"

frames=${wwwdisk}/sst.kml

echo '<?xml version="1.0" encoding="UTF-8"?>' > $frames
echo '<kml xmlns="http://earth.google.com/kml/2.2">' >> $frames
echo '<Folder>' >> $frames
echo '	<ScreenOverlay>' >> $frames
echo '		<name>Key</name>' >> $frames
echo '		<visibility>1</visibility>' >> $frames
echo '		<Icon>' >> $frames
echo "			<href>${www}/../images/sst.png</href>" >> $frames
echo '		</Icon>' >> $frames
echo '		<overlayXY x="0" y="1" xunits="fraction" yunits="fraction"/>' >> $frames
echo '		<screenXY x="0" y="1" xunits="fraction" yunits="fraction"/>' >> $frames
echo '		<rotationXY x="0" y="0" xunits="fraction" yunits="fraction"/>' >> $frames
echo '		<size x="0" y="0" xunits="fraction" yunits="fraction"/>' >> $frames
echo '	</ScreenOverlay>' >> $frames
echo '  <name>frames</name>' >> $frames
echo '  <description></description>' >> $frames
echo '  <NetworkLink>' >> $frames
echo '    <visibility>1</visibility>' >> $frames
echo '    <open>0</open>' >> $frames
echo '    <Url>' >> $frames
echo "      <href>${www}/sst.kmz</href>" >> $frames
echo '    </Url>' >> $frames
echo '  </NetworkLink>' >> $frames
echo '</Folder>' >> $frames
echo '</kml>' >> $frames
