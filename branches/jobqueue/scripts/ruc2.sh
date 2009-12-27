#!/bin/bash
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

wwwdisk="/home/rush/winkey/public_html//kml/ruc2"
www="atmos.ucsd.edu//kml/ruc2"

#CONDUIT	^data/nccf/com/(ruc/prod/ruc2a.[0-9]*)/ruc2.t([0-9][0-9])z.pgrb20[af][0-9nl]*.grib2 !grib2/ncep/RUC2/#000/[0-9]*F0([0-9]*)/(HGHT|TMPK|RELH|UREL;VREL)/(925|850|700|500|300) Pa PRES!
#	FILE	data/conduit/\1/\2.\3.\4.\5.grib2
#CONDUIT	^data/nccf/com/(ruc/prod/ruc2a.[0-9]*)/ruc2.t([0-9][0-9])z.pgrb20[af][0-9nl]*.grib2 !grib2/ncep/RUC2/#000/[0-9]*F0([0-9]*)/(HGHT|TMPK|RELH|UREL;VREL)/(925|850|700|500|300) Pa PRES!
#	EXEC	/usr/local/bin/ruc2.sh data/conduit/\1/\2.\3.\4.\5.grib2 \2 \3 \4 \5

#CONDUIT	^data/nccf/com/(ruc/prod/ruc2a.[0-9]*)/ruc2.t([0-9][0-9])z.pgrb20[af][0-9nl]*.grib2 !grib2/ncep/RUC2/#000/[0-9]*F0([0-9]*)/(CAPE|PWTR)/(0) - NONE!
#	FILE	data/conduit/\1/\2.\3.\4.\5.grib2
#CONDUIT	^data/nccf/com/(ruc/prod/ruc2a.[0-9]*)/ruc2.t([0-9][0-9])z.pgrb20[af][0-9nl]*.grib2 !grib2/ncep/RUC2/#000/[0-9]*F0([0-9]*)/(CAPE|PWTR)/(0) - NONE!
#	EXEC	/usr/local/bin/ruc2.sh data/conduit/\1/\2.\3.\4.\5.grib2 \2 \3 \4 \5

path="$1"
run="$2"
hour="$3"
prod="$4"
level="$5"
tmp="/tmp"

if [[ "$hour" == "" ]]
then
	hour="00"
fi

if [[ ! -d "${wwwdisk}/${run}" ]]
then
	mkdir -p "${wwwdisk}/${run}"
fi

function thick {
	spath="${path/HGHT.1000/HGHT.${1}}"
	if [[ -f $spath ]]
	then
		if [[ $hour == "00" ]]
		then
			mkrootkml ${1}thk
		fi
		diffplot "$spath" "$path" ${1}thk 1 1 20 $hour 01
		
		
	fi
}

function thick2 {
	spath="${path/HGHT.${1}/HGHT.1000}"
	if [[ -f $spath ]]
	then
		if [[ $hour == "00" ]]
		then
			mkrootkml ${1}thk
		fi
		diffplot "$path" "$spath" ${1}thk 1 1 20 $hour 01
		
		
	fi
}

##### plot height #####

if [[ "$prod" == "HGHT" ]]
then
	if [[ "$hour" == "00" ]]
	then
		mkrootkml "${level}hgt"
	fi
	
	plot "$path" "${level}hgt" 1 20 $hour 01 "-H"

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

if [[ "$prod" == "TMPK" ]]
then
	if [[ "$hour" == "00" ]]
	then
		mkrootkml "${level}t"
	fi
	
	plot "$path" "${level}t" 1 1 $hour 01

fi

##### plot rh #####

if [[ "$prod" == "RELH" ]]
then
	if [[ "$hour" == "00" ]]
	then
		mkrootkml "${level}rh"
	fi
	
	plot "$path" "${level}rh" 1 10 $hour 01

fi

##### plot wind #####

if [[ "$prod" == "UREL;VREL" ]]
then
	if [[ "$hour" == "00" ]]
	then
		mkrootkml "${level}wind"
	fi
	
	windplot "$path" "$path" "${level}wind" 1.0 1.1 10 $hour 01

fi

##### plot cape #####

if [[ "$prod" == "CAPE" ]]
then
	if [[ "$hour" == "00" ]]
	then
		mkrootkml "cape"
	fi
	
	plot "$path" "cape" 1 200 $hour 01

fi

##### plot pwat #####

if [[ "$prod" == "PWTR" ]]
then
	if [[ "$hour" == "00" ]]
	then
		mkrootkml "pwat"
	fi
	
	plot "$path" "pwat" 1 4 $hour 01 "-I"

fi

#### plot percip #####

if [[ "$prod" == "PR03" ]]
then
	if [[ "$hour" == "03" ]]
	then
		mkrootkml "pcp"
	fi
	
	plot "$path" "pcp" 1 4 $hour 01

fi

#### plot mmsl #####

if [[ "$prod" == "MMSL" ]]
then
	if [[ "$hour" == "00" ]]
	then
		mkrootkml "pmsl"
	fi
	
	plot "$path" "pmsl" 1 200 $hour 01 "-H"

fi

