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

wwwdisk="/home/rush/public_html/weather/kml/nam_conus"
www="http://winkey.org/weather/kml/nam_conus"


path="$1"
run="$2"
hour="$3"
prod="$4"
level="$5"
tmp="/tmp"

hour="${hour:1}"

if [[ ! -d "${wwwdisk}/${run}" ]]
then
	mkdir -p "${wwwdisk}/${run}"
fi

##### plot height #####

if [[ "$prod" == "HGHT" ]]
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
	
	plot "$path" "${level}hgt" 1 20 $hour 03

	rm "$path"
fi

##### plot temp #####

if [[ "$prod" == "TMPK" ]]
then
	if [[ "$hour" == "00" ]]
	then
		mkrootkml "${level}t"
	fi
	
	plot "$path" "${level}t" 1 1 $hour 03

	rm "$path"
fi

##### plot rh #####

if [[ "$prod" == "RELH" ]]
then
	if [[ "$hour" == "00" ]]
	then
		mkrootkml "${level}rh"
	fi
	
	plot "$path" "${level}rh" 1 5 $hour 03

	rm "$path"
fi

##### plot wind #####

if [[ "$prod" == "UREL" ]]
then
	vpath=$(echo "$path" | sed s/UREL/VREL/)
	
	if [[ -f "$vpath" ]]
	then
		if [[ "$hour" == "00" ]]
		then
			mkrootkml "${level}wind"
		fi
		
		windplot "$path" "$vpath" "${level}wind" 1.0 1.0 10 $hour 03

		rm "$path"
		rm "$vpath"
	fi
fi

if [[ "$prod" == "VREL" ]]
then
	upath=$(echo "$path" | sed s/VREL/UREL/)
	
	if [[ -f "$upath" ]]
	then
		if [[ "$hour" == "00" ]]""""
		then
			mkrootkml "${level}wind"
		fi
		
		windplot "$upath" "$path" "${level}wind" 1.0 1.0 10 $hour 03
		
		rm "$path"
		rm "$upath"
	fi
fi

##### plot cape #####

if [[ "$prod" == "CAPE" ]]
then
	if [[ "$hour" == "00" ]]
	then
		mkrootkml "cape"
	fi
	
	plot "$path" "cape" 1 200 $hour 03
	
	rm "$path"
fi

##### plot pwat #####

if [[ "$prod" == "PWTR" ]]
then
	if [[ "$hour" == "00" ]]
	then
		mkrootkml "pwat"
	fi
	
	plot "$path" "pwat" 1 4 $hour 03
	
	rm "$path"
fi

##### plot percip #####

if [[ "$prod" == "P03M" ]]
then
	if [[ "$hour" == "03" ]]
	then
		mkrootkml "pcp"
	fi
	
	plot "$path" "pcp" 1 4 $hour 03

	rm "$path"
fi

#### plot pmsl #####

if [[ "$prod" == "PMSL" ]]
then
	if [[ "$hour" == "00" ]]
	then
		mkrootkml "pmsl"
	fi
	
	plot "$path" "pmsl" 1 200 $hour 03
	rm "$path"
fi

##### plot POPF03 #####

if [[ "$prod" == "POPF03" ]]
then
	if [[ "$hour" == "03" ]]
	then
		mkrootkml "popf"
	fi
	
	plot "$path" "popf" 1 4 $hour 03

	rm "$path"
fi

##### plot TSTM03 #####

if [[ "$prod" == "TSTM03" ]]
then
	if [[ "$hour" == "03" ]]
	then
		mkrootkml "tstm"
	fi
	
	plot "$path" "tstm" 1 4 $hour 03

	rm "$path"
fi

##### plot POP03 #####

if [[ "$prod" == "POP03" ]]
then
	if [[ "$hour" == "03" ]]
	then
		mkrootkml "pop"
	fi
	
	plot "$path" "pop" 1 4 $hour 03

	rm "$path"
fi

##### plot POPZ03 #####

if [[ "$prod" == "POPZ03" ]]
then
	if [[ "$hour" == "03" ]]
	then
		mkrootkml "popz"
	fi
	
	plot "$path" "popz" 1 4 $hour 03

	rm "$path"
fi
