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
www="http://atmos.ucsd.edu/kml/rtma_ak"

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

##### plot temp #####

if [[ "$prod" == "TMPK" ]]
then
	mkrootkml "t"
	plot "$path" "t" 1 1.5 00 01
	rm "$path"
fi

##### plot dewpoint #####

if [[ "$prod" == "DWPK" ]]
then
	mkrootkml "dp"
	plot "$path" "dp" 1 1.5 00 01
	rm "$path"
fi

##### plot wind #####

if [[ "$prod" == "UREL" ]]
then
	vpath=$(echo $path | sed s/UREL/VREL/)
	if [[ -f $vpath ]]
	then
		mkrootkml "wind"
		windplot "$path" "$vpath" "wind" 1.0 1.0 5 00 01
		rm "$path"
		rm "$vpath"
	fi
fi

if [[ "$prod" == "VREL" ]]
then
	upath=$(echo $path | sed s/VREL/UREL/)
	if [[ -f upath ]]
	then
		mkrootkml "wind"
		windplot "$upath" "$path" "wind" 1.0 1.0 5 00 01
		rm "$path"
		rm "$upath"
	fi
fi
