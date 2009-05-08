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

wwwdisk="/home/rush/public_html/weather/kml/gfs"
www="http://atmos.ucsd.edu//kml/gfs"

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

##### plot height #####

if [[ "$prod" == "HGHT" ]]
then
	if [[ "$hour" == "00" ]]
	then
		mkrootkml "${level}hgt"
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
	rm "$path"
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
	
	plot "$path" "pwat" 1 4 $hour 03 "-I"
	rm "$path"
fi

##### plot percip #####

if [[ "$prod" == "P06M" ]]
then
	if [[ "$hour" == "06" ]]
	then
		mkrootkml "pcp"
	fi
	
	plot "$path" "pcp" 1 4 $hour 06 "-I"
	
	## WXTS ##
	
	spath=$(echo "$path" | sed s/P06M/WXTS06/')
	
	if [[ -f "$spath" ]]
	then
		if [[ "$hour" == "06" ]]
		then
			mkrootkml "snow"
		fi
		
		andplot "$path" "$spath" "snow" 1.0 1.0 4 $hour 06 "-I"
		
		rm "$spath"
	fi
	
	## WXTZ ##
	
	zpath=$(echo "$path" | sed s/P06M/WXTZ06/)
	
	if [[ -f "$zpath" ]]
	then
		if [[ "$hour" == "06" ]]
		then
			mkrootkml "frez"
		fi
		
		andplot "$path" "$zpath" "frez" 1.0 1.0 4 $hour 06 "-I"
		
		rm "$zpath"
	fi
	
	## WXTR ##
	
	rpath=$(echo "$path" | sed s/P06M/WXTR06/)
	
	if [[ -f "$rpath" ]]
	then
		if [[ "$hour" == "06" ]]
		then
			mkrootkml "rain"
		fi
		
		andplot "$path" "$rpath" "rain" 1.0 1.0 4 $hour 06 "-I"
		
		rm "$rpath"
	fi
	
	## WXTP ##
	
	ppath=$(echo "$path" | sed s/P06M/WXTP06/)
	
	if [[ -f "$ppath" ]]
	then
		if [[ "$hour" == "06" ]]
		then
			mkrootkml "pellet"
		fi
		
		andplot "$path" "$ppath" "pellet" 1.0 1.0 4 $hour 06 "-I"
		
		rm "$ppath"
	fi
fi

#### WXTS ####

if [[ "$prod" == "WXTS06" ]]
then
	
	ppath=$(echo "$path" | sed s/WXTS06/P06M/)
	
	if [[ -f "$ppath" ]]
	then
		if [[ "$hour" == "06" ]]
		then
			mkrootkml "snow"
		fi
		
		andplot "$ppath" "$path" "snow" 1.0 1.0 4 $hour 06 "-I"
		
		rm "$path"
	fi
fi

#### WXTZ ####

if [[ "$prod" == "WXTZ06" ]]
then
	
	ppath=$(echo "$path" | sed s/WXTZ06/P06M/)
	
	if [[ -f "$ppath" ]]
	then
		if [[ "$hour" == "06" ]]
		then
			mkrootkml "frez"
		fi
		
		andplot "$ppath" "$path" "frez" 1.0 1.0 4 $hour 06 "-I"
		
		rm "$path"
	fi
fi

#### WXTR ####

if [[ "$prod" == "WXTR06" ]]
then
	
	ppath=$(echo "$path" | sed s/WXTR06/P06M/)
	
	if [[ -f "$ppath" ]]
	then
		if [[ "$hour" == "06" ]]
		then
			mkrootkml "rain"
		fi
		
		andplot "$ppath" "$path" "rain" 1.0 1.0 4 $hour 06 "-I"
		
		rm "$path"
	fi
fi

#### WXTP ####
	
if [[ "$prod" == "WXTP06" ]]
then
	ppath=$(echo "$path" | sed s/WXTP06/P06M/)
	
	if [[ -f "$ppath" ]]
	then
		if [[ "$hour" == "06" ]]
		then
			mkrootkml "pellet"
		fi
		
		andplot "$ppath" "$path" "pellet" 1.0 1.0 4 $hour 06 "-I"
		
		rm "$path"
	fi
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

