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

wwwdisk="/home/rush/winkey/public_html//kml/gfs"
www="atmos.ucsd.edu//kml/gfs"

#CONDUIT ^data/nccf/com/(gfs/prod/gfs.[0-9]*)/gfs.t([0-9][0-9])z.pgrb2f([0-9]*) !grib2/ncep/GFS/#000/.*/(HGHT|TMPK|RELH|UREL;VREL)/(925|850|700|500|300) Pa PRES!
#	EXEC	/usr/local/bin/gfs2.sh data/conduit/\1/\2.\3.\4.\5.grib2 \2 \3 \4 \5

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
		diffplot "$spath" "$path" ${1}thk 1 1 20 $hour 03
		
		
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
		diffplot "$path" "$spath" ${1}thk 1 1 20 $hour 03
		
		
	fi
}

##### plot height #####

if [[ "$prod" == "HGHT" ]]
then
	if [[ "$hour" == "00" ]]
	then
		mkrootkml "${level}hgt"
	fi
	
	plot "$path" "${level}hgt" 1 20 $hour 03  "-H"
	
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


	plot "$path" "${level}t" 1 1 $hour 03

fi

##### plot rh #####

if [[ "$prod" == "RELH" ]]
then
	if [[ "$hour" == "00" ]]
	then
		mkrootkml "${level}rh"
	fi
	
	plot "$path" "${level}rh" 1 10 $hour 03

fi

##### plot wind #####

if [[ "$prod" == "UREL;VREL" ]]
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
		
	windplot "$path" "$path" "${level}wind" 1.0 1.1 $interval $hour 03

fi

##### plot cape #####

if [[ "$prod" == "CAPE" ]]
then
	if [[ "$hour" == "00" ]]
	then
		mkrootkml "cape"
	fi
	
	plot "$path" "cape" 1 200 $hour 03

fi

##### plot pwat #####

if [[ "$prod" == "PWTR" ]]
then
	if [[ "$hour" == "00" ]]
	then
		mkrootkml "pwat"
	fi
	
	plot "$path" "pwat" 1 4 $hour 03 "-I"

fi

function wx {
	spath=$(echo "$path" | sed s/P06M/${1}06/)
	
	if [[ -f "$spath" ]]
	then
		if [[ "$hour" == "06" ]]
		then
			mkrootkml $2
		fi
		
		andplot "$path" "$spath" $2 1.0 1.0 4 $hour 06 "-I"
		

	fi
}

function wx2 {
	ppath=$(echo "$path" | sed s/${1}06/P06M/)	
	if [[ -f "$spath" ]]
	then
		if [[ "$hour" == "06" ]]
		then
			mkrootkml $2
		fi
		
		andplot "$spath" "$path" $2 1.0 1.0 4 $hour 06 "-I"
		

	fi
}
	
##### plot percip #####

if [[ "$prod" == "P06M" ]]
then
	if [[ "$hour" == "06" ]]
	then
		mkrootkml "pcp"
	fi
	
	plot "$path" "pcp" 1 4 $hour 06 "-I"
	
	## WXTS ##
	
	wx WXTS snow
	wx WXTZ frez
	wx WXTR rain
	wx WXTP pellet
fi

#### WXTS ####

if [[ "$prod" == "WXTS06" ]]
then
	wx2 WXTS snow
fi

#### WXTZ ####

if [[ "$prod" == "WXTZ06" ]]
then
	wx2 WXTZ frez
fi

#### WXTR ####

if [[ "$prod" == "WXTR06" ]]
then
	wx2 WXTR rain
fi

#### WXTP ####
	
if [[ "$prod" == "WXTP06" ]]
then
	wx2 WXTP pellet
fi

#### plot pmsl #####

if [[ "$prod" == "PMSL" ]]
then
	if [[ "$hour" == "00" ]]
	then
		mkrootkml "pmsl"
	fi
	
	plot "$path" "pmsl" 1 200 $hour 03 "-H"

fi


