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

db="nogaps"

source /usr/local/bin/generic2.sh

wwwdisk="/home/rush/winkey/public_html//kml/nogaps"
www="atmos.ucsd.edu//kml/nogaps"


path="$1"
run="$2"
hour="$3"
prod="$4"
level="$5"
tmp="/tmp"

hour=${hour#0}

if [[ ! -d "${wwwdisk}/${run}" ]]
then
	mkdir -p "${wwwdisk}/${run}"
fi


function thick {
	spath="${path/1000.geop_ht/${1}.geop_ht}"
	if [[ -f $spath ]]
	then
		if [[ $hour == "00" ]]
		then
			mkrootkml ${1}thk
		fi
		diffplot "$spath" "$path" ${1}thk 1 1 20 $hour 03
		
		
	fi
}

function thick2 {
	spath="${path/${1}.geop_ht/1000.geop_ht}"
	if [[ -f $spath ]]
	then
		if [[ $hour == "00" ]]
		then
			mkrootkml ${1}thk
		fi
		diffplot "$path" "$spath" ${1}thk 1 1 20 $hour 03
		
		
	fi
}

##### plot height #####

if [[ "$prod" == "geop_ht" ]]
then

	if [[ "$hour" == "00" ]]
	then
		mkrootkml "${level}hgt"
	fi	
	plot "$path" "${level}hgt" 1 20 $hour 03 "-H"
	
	##### plot thickness #####
	
	if [[ $level == 1000 ]]
	then
		thick 925
		thick 850
		thick 700
		thick 500
	else
		if [[ $level == 925 || $level == 850 || $level == 700 || $level == 500 ]]
		then
			
			thick2 $level
		fi
	fi
fi

##### plot temp #####

if [[ "$prod" == "air_temp" ]]
then
	if [[ "$hour" == "00" ]]
	then
		mkrootkml "${level}t"
	fi
	plot "$path" "${level}t" 1 1 $hour 03

fi

##### plot rh #####

if [[ "$prod" == "rltv_hum" ]]
then

	if [[ "$hour" == "00" ]]
	then
		mkrootkml "${level}rh"
	fi	
	plot "$path" "${level}rh" 1 10 $hour 03

fi

##### plot wind #####

if [[ "$prod" == "wnd_ucmp" ]]
then
	vpath=$(echo "$path" | sed s/wnd_ucmp/wnd_vcmp/)
	
	if [[ -f "$vpath" ]]
	then

		if [[ "$level" -gt "500" ]]
		then
			interval=5
		else
			interval=7
		fi
		if [[ "$hour" == "00" ]]
		then
			mkrootkml "${level}wind"
		fi		
		windplot "$path" "$vpath" "${level}wind" 1.0 1.0 $interval $hour 03


	fi
fi

if [[ "$prod" == "wnd_vcmp" ]]
then
	upath=$(echo "$path" | sed s/wnd_vcmp/wnd_ucmp/)
	
	if [[ -f "$upath" ]]
	then

		if [[ "$level" -gt "500" ]]
		then
			interval=5
		else
			interval=7
		fi
		if [[ "$hour" == "00" ]]
		then
			mkrootkml "${level}wind"
		fi				
		windplot "$upath" "$path" "${level}wind" 1.0 1.0 $interval $hour 03
		

	fi
fi

	
##### plot percip #####

 if [[ "$prod" == "ttl_prcp" ]]
then

	if [[ "$hour" == "03" ]]
	then
		mkrootkml "pcp"
	fi
	plot "$path" "pcp" 1 4 $hour 03 "-I"
	

fi


#### plot pmsl #####

if [[ "$prod" == "pres" ]] && [[ "$level" == "0" ]]
then

	if [[ "$hour" == "00" ]]
	then
		mkrootkml "pmsl"
	fi	
	plot "$path" "pmsl" 1 200 $hour 03 "-H"

fi


