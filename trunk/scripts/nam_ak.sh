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

source /usr/local/bin/generic.sh

serv="ftp://ftpprd.ncep.noaa.gov/pub/data/nccf/com/nam/prod/"
servb="http://www.ftp.ncep.noaa.gov/data/nccf/com/nam/prod/"
wwwdisk="/home/rush/public_html/weather/kml/nam_ak"
www="http://atmos.ucsd.edu//kml/nam_ak/"

times=`seq -f "%02g" 0 1 48`

if [[ ! -d "${wwwdisk}/${run}" ]]
then
	mkdir -p "${wwwdisk}/${run}"
fi

function doplot {
	datee=$1
	run=$2
	timee=$3
	
	gribfile="aknmm.t${run}z.awpreg${timee}.tm00.grib2"
	
	if ! getgrib "${servb}hiresw.${datee}/" "$gribfile"
	then
		return
	fi
	
	plot $gribfile 925hgt 104 20 $timee&
	plot $gribfile 925t 105 1 $timee&
	plot $gribfile 925rh 103 5 $timee&
	windplot $gribfile $gribfile 925wind 107 108 5 $timee&
	wait
	
	plot $gribfile 850hgt 98 20 $timee&
	plot $gribfile 850t 99 1 $timee&
	plot $gribfile 850rh 97 5 $timee&
	windplot $gribfile $gribfile 850wind 101 102 5 $timee&
	wait

	plot $gribfile 700hgt 92 20 $timee&
	plot $gribfile 700t 93 1 $timee&
	plot $gribfile 700rh 91 5 $timee&
	windplot $gribfile $gribfile 700wind 95 96 5 $timee&
	wait

	plot $gribfile 500hgt 86 20 $timee&
	plot $gribfile 500t 87 1 $timee&
	plot $gribfile 500rh 85 5 $timee&
	windplot $gribfile $gribfile 500wind 89.0 90.0 10 $timee&
	wait

	plot $gribfile 300hgt 74 20 $timee&
	plot $gribfile 300t 75 1 $timee&
	plot $gribfile 300rh 73 5 $timee&
	windplot $gribfile $gribfile 300wind 77.0 78.0 10 $timee&
	wait
	
	plot $gribfile pwat 18 2 $timee&
	plot $gribfile cape 20 200 $timee&
  plot $gribfile pmsl 2 200 $timee&
  plot $gribfile pcp 12 4 $timee&
	wait
	
	andplot $gribfile "$path" "snow" 12 14 4 $timee&
	andplot $gribfile "$path" "frez" 12 16 4 $timee&
	andplot $gribfile "$path" "rain" 12 17 4 $timee&
	andplot $gribfile "$path" "pellet" 12 15 $timee&
	wait

	#cleanup
	
	rm "${tmp}/${gribfile}"
	
}

mktempfiledir "$tmp"


if [[ ! -h "${wwwdisk}/latest" ]]
then
	rm -f "${wwwdisk}/latest"
fi
ln -s "${wwwdisk}/${run}" "${wwwdisk}/latest"

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

for i in $times
do
	time doplot $datee $run $i
done

#cleanup

if [ -d "$tmp" ]
then
        rm -r "$tmp"
fi

