#!/bin/sh
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

source /usr/local/bin/generic2.sh

wwwdisk="/home/rush/public_html/weather/kml/forecaster"
www="http://atmos.ucsd.edu/kml/forecaster"

#NGRID ^[LM]DG[A-Z]98 KNHC .* !grib2/ncep/FORECASTER/#000/([0-9]{8})([0-9][0-9])00F[0-9]{3}/SPED([0-9]{2,3})00(17|25|32)P.*
#	FILE	data/ngrid/forecaster/\1\2.\2.\3.\4.grib2
#NGRID ^[LM]DG[A-Z]98 KNHC .* !grib2/ncep/FORECASTER/#000/([0-9]{8})([0-9][0-9])00F[0-9]{3}/SPED([0-9]{2,3})00(17|25|32)P.*
#	EXEC	/usr/local/bin/forecaster.sh data/ngrid/forecaster/\1\2.\2.\3.\4.grib2 \2 \3 \4

path="$1"
run="$2"
hour="$3"
prod="$4"

tmp="/tmp"

if [[ "$hour" == "" ]]
then
	hour="00"
fi

if [[ ! -d "${wwwdisk}/${run}" ]]
then
	mkdir -p "${wwwdisk}/${run}"
fi

frames=${wwwdisk}/${run}/prob${prod}.kml

if [[ $(($(stat -c %Y ${frames})+21600)) -lt $(date "+%s") ]]
then
	mkrootkml "prob${prod}"
fi
	
zip="${wwwdisk}/${run}/prob${prod}${hour}.kmz"
kml="prob${prod}${hour}.kml"

if [[ -f "$zip" ]]
then
	rm "$zip"
fi
	
nice -n 10 grib_contour -g "${path}" -m 1 -i 5 -s prob -k $kml -z "$zip"
appendkml "prob${prod}" $hour 06
	
rm "$path"
