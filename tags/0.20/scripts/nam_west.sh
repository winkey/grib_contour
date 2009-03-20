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

serv="ftp://ftpprd.ncep.noaa.gov/pub/data/nccf/com/nam/prod/"
servb="http://www.ftp.ncep.noaa.gov/data/nccf/com/nam/prod/"
wwwdisk="/home/rush/public_html/weather/kml/nam_west"
www="http://atmos.ucsd.edu//kml/nam_west/"


run=$1

times=`seq -f "%02g" 0 1 48`



function doplot {
	datee=$1
	run=$2
	timee=$3
	
	gribfile="eastnmm.t${run}z.awpreg${timee}.tm00.grib2"
	
	if ! getgrib "${servb}hiresw.${datee}/" "$gribfile" "/tmp"
	then
		return
	fi
	
	gribfile="/tmp/${gribfile}"

	plot $gribfile 925hgt 104 20 $timee 01 &
	plot $gribfile 925t 105 1 $timee 01 &
	plot $gribfile 925rh 103 5 $timee 01 &
	windplot $gribfile $gribfile 925wind 107 108 5 $timee 01 &
	wait
	
	plot $gribfile 850hgt 98 20 $timee 01 &
	plot $gribfile 850t 99 1 $timee 01 &
	plot $gribfile 850rh 97 5 $timee 01 &
	windplot $gribfile $gribfile 850wind 101 102 5 $timee 01 &
	wait

	plot $gribfile 700hgt 92 20 $timee 01 &
	plot $gribfile 700t 93 1 $timee 01 &
	plot $gribfile 700rh 91 5 $timee 01 &
	windplot $gribfile $gribfile 700wind 95 96 5 $timee 01 &
	wait

	plot $gribfile 500hgt 86 20 $timee 01 &
	plot $gribfile 500t 87 1 $timee 01 &
	plot $gribfile 500rh 85 5 $timee 01 &
	windplot $gribfile $gribfile 500wind 89.0 90.0 10 $timee 01 &
	wait

	plot $gribfile 300hgt 74 20 $timee 01 &
	plot $gribfile 300t 75 1 $timee 01 &
	plot $gribfile 300rh 73 5 $timee 01 &
	windplot $gribfile $gribfile 300wind 77.0 78.0 10 $timee 01 &
	wait
	
	plot $gribfile pwat 18 4 $timee 01 &
	plot $gribfile cape 20 200 $timee 01 &
	plot $gribfile pmsl 2 200 $timee 01 &
	if [[ "$timee" != "00" ]] && [[ "$timee" != "01" ]]
	then
		plot $gribfile pcp 12 1 $timee 01 &
	fi
	wait
	
	if [[ "$timee" != "00" ]] && [[ "$timee" != "01" ]]
	then
		andplot $gribfile $gribfile "snow" 12 14 1 $timee 01 &
		andplot $gribfile $gribfile "frez" 12 16 1 $timee 01 &
		andplot $gribfile $gribfile "rain" 12 17 1 $timee 01 &
		andplot $gribfile $gribfile "pellet" 12 1 $timee 01 &
		wait
	fi

	#cleanup
	
	rm "${tmp}/${gribfile}"
	
}

mktempfiledir "$tmp"

mkrootkml 925hgt
mkrootkml 925t
mkrootkml 925rh
mkrootkml 925wind

mkrootkml 850hgt
mkrootkml 850t
mkrootkml 850rh
mkrootkml 850wind

mkrootkml 700hgt
mkrootkml 700t
mkrootkml 700rh
mkrootkml 700wind

mkrootkml 500hgt
mkrootkml 500t
mkrootkml 500rh
mkrootkml 500wind

mkrootkml 300hgt
mkrootkml 300t
mkrootkml 300rh
mkrootkml 300wind

mkrootkml pwat
mkrootkml cape
mkrootkml pmsl
mkrootkml pcp

mkrootkml snow
mkrootkml frez
mkrootkml rain
mkrootkml pellet

for i in $times
do
	time doplot $datee $run $i
done

#cleanup


