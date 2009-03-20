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

wwwdisk="/home/rush/public_html/weather/kml/ecmwf"
www="http://atmos.ucsd.edu//kml/ecmwf"



path="$1"
grid="$2"
datee="$3"
run="$4"
hour="${5#0}"
prod="$6"
level="$7"
tmp="/tmp"

if [[ "$hour" == "" ]]
then
	hour="00"
fi

if [[ ! -d "${wwwdisk}/${run}" ]]
then
	mkdir -p "${wwwdisk}/${run}"
fi

##### plot height #####

if [[ "$prod" == "HGT" ]]
then
	if [[ "$hour" == "00" ]]
	then
		mkrootkml "${level}hgt"
		if [[ ! -h "${wwwdisk}/latest" ]]
		then
			rm -f "${wwwdisk}/latest"
		fi
		ln -s "${wwwdisk}/${run}" "${wwwdisk}/latest"
	fi
	
	plot "$path" "${level}hgt" 1 20 $hour 24 $grid
	rm "$path"
fi

##### plot temp #####

if [[ "$prod" == "TMP" ]]
then
	if [[ "$hour" == "00" ]]
	then
		mkrootkml "${level}t"
	fi
	
	plot "$path" "${level}t" 1 1 $hour 03 $grid
	rm "$path"
fi

##### plot rh #####

if [[ "$prod" == "RH" ]]
then
	if [[ "$hour" == "00" ]]
	then
		mkrootkml "${level}rh"
	fi
	
	plot "$path" "${level}rh" 1 5 $hour 03 $grid
	rm "$path"
fi

if [[ "$prod" == "UGRD" ]]
then
	vpath=$(echo "$path" | sed s/UGRD/VREL/)
	
	if [[ -f "$vpath" ]]
	then
		if [[ "$hour" == "00" ]]
		then
			mkrootkml "${level}wind"
		fi
		
		if [[ "$level" -gt "500" ]]
		then
			interval=5
		else
			interval=7
		fi
		
		windplot "$path" "$vpath" "${level}wind" 1.0 1.0 $interval $hour 03 $grid

		rm "$path"
		rm "$vpath"
	fi
fi

if [[ "$prod" == "VREL" ]]
then
	upath=$(echo "$path" | sed s/VGRD/UGRD/)
	
	if [[ -f "$upath" ]]
	then
		if [[ "$hour" == "00" ]]
		then
			mkrootkml "${level}wind"
		fi
		
		if [[ "$level" -gt "500" ]]
		then
			interval=5
		else
			interval=7
		fi
		
		windplot "$upath" "$path" "${level}wind" 1.0 1.0 $interval $hour 03 $grid
		
		rm "$path"
		rm "$upath"
	fi
fi

#### plot pmsl #####

if [[ "$prod" == "PRMSL" ]]
then
	if [[ "$hour" == "00" ]]
	then
		mkrootkml "pmsl"
	fi
	
	plot "$path" "pmsl" 1 200 $hour 03 $grid
	rm "$path"
fi



