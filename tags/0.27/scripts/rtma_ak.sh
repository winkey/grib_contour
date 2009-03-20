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

wwwdisk="/home/rush/public_html/weather/kml/rtma_ak"
www="/home/rush/public_html/weather/kml/rtma_ak"

#NGRID	^L[A-Z][AM]A98 KWBR .* !grib2/ncep/RTMA/#201/([0-9]{8})([0-9]{2})00F000/(DRCT|SPED|UREL|VREL|TMPK|DWPK)/
#	EXEC	/usr/local/bin/rtma_ak.sh data/ngrid/rtma/201/\1\2.\2.\3.grib2 \2 \3

path="$1"
run="$2"
prod="$3"

tmp="/tmp"

hour="00"

if [[ ! -d "${wwwdisk}/${run}" ]]
then
	mkdir -p "${wwwdisk}/${run}"
fi

if [[ ! -h "${wwwdisk}/latest" ]]
then
	rm -f "${wwwdisk}/latest"
fi
ln -s "${wwwdisk}/${run}" "${wwwdisk}/latest"



##### plot temp #####

if [[ "$prod" == "TMPK" ]]
then
	zip="${wwwdisk}/${run}/t.kmz"
	kml="t.kml"

	if [[ -f "$zip" ]]
	then
		rm "$zip"
	fi

	nice -n 10 grib_contour -g "${path}" -m 1 -i 1.5 -s t -k $kml -z "$zip"
	
	rm "$path"
fi

##### plot dewpoint #####

if [[ "$prod" == "DWPK" ]]
then
	zip="${wwwdisk}/${run}/dp.kmz"
	kml="dp.kml"

	if [[ -f "$zip" ]]
	then
		rm "$zip"
	fi

	nice -n 10 grib_contour -g "${path}" -m 1 -i 1.5 -s dp -k $kml -z "$zip"
	
	rm "$path"
fi

##### plot wind #####

if [[ "$prod" == "UREL" ]]
then
	vpath=$(echo $path | sed s/UREL/VREL/)
	if [[ -f "$vpath" ]]
	then

		zip="${wwwdisk}/${run}/wind.kmz"
		kml="wind.kml"
		
		if [[ -f "$zip" ]]
			then
			rm "$zip"
		fi
	
		nice -n 10 grib_contour -w -u "$path" -v "$vpath" -U 1.0 -V 1.0 -i 5 -s wind -k $kml -z "$zip"

		rm "$path"
		rm "$vpath"
	fi
fi

if [[ "$prod" == "VREL" ]]
then
	upath=$(echo $path | sed s/VREL/UREL/)
	if [[ -f upath ]]
	then

		nice -n 10 grib_contour -w -u "$upath" -v "$path" -U 1.0 -V 1.0 -i 5 -s wind -k $kml -z "$zip"

		
		rm "$path"
		rm "$upath"
	fi
fi
