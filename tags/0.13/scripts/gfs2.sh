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
www="http://winkey.org/weather/kml/gfs"

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
	
	windplot "$path" "$path" "${level}wind" 1.0 1.1 10 $hour 03
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
	
	plot "$path" "pwat" 1 4 $hour 03
	rm "$path"
fi

#### plot percip #####

if [[ "$prod" == "PR03" ]]
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

#grib2/ncep/GFS/#000/200805291200F021/WXTS03/0 - NONE 000197 snow
#grib2/ncep/GFS/#000/200805291200F021/WXTZ03/0 - NONE 000199 frez rain
#grib2/ncep/GFS/#000/200805291200F021/WXTR03/0 - NONE 000200 rain
#grib2/ncep/GFS/#000/200805291200F021/WXTP03/0 - NONE 000198 hail
#grib2/ncep/GFS/#000/200805291200F021/PR03/0 - NONE 000193 precip
