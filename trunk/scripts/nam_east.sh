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
wwwdisk="/home/rush/public_html/weather/kml/nam_east"
www="http://winkey.org/weather/kml/nam_east/"

times=`seq 0 3 48`

function doplot {
	datee=$1
	run=$2
	timee=$3
	
	gribfile="eastarw.t${run}z.awpreg${timee}.tm00.grib2"
	
	if ! getgrib "${servb}hiresw.${datee}/" "$gribfile"
	then
		return
	fi
	
	plot $gribfile 925hgt 88 20 $timee&
	plot $gribfile 925t 89 1 $timee&
	plot $gribfile 925rh 87 5 $timee&
	windplot $gribfile 925wind 91 10 $timee&
	wait
	
	plot $gribfile 850hgt 83 20 $timee&
	plot $gribfile 850t 84 1 $timee&
	plot $gribfile 850rh 82 5 $timee&
	windplot $gribfile 850wind 86 10 $timee&
	wait

	plot $gribfile 700hgt 78 20 $timee&
	plot $gribfile 700t 79 1 $timee&
	plot $gribfile 700rh 77 5 $timee&
	windplot $gribfile 700wind 81 10 $timee&
	wait

	plot $gribfile 500hgt 73 20 $timee&
	plot $gribfile 500t 74 1 $timee&
	plot $gribfile 500rh 72 5 $timee&
	windplot $gribfile 500wind 76 10 $timee&
	wait

	plot $gribfile 300hgt 63 20 $timee&
	plot $gribfile 300t 64 1 $timee&
	plot $gribfile 300rh 62 5 $timee&
	windplot $gribfile 300wind 66 10 $timee&
	wait
	
	plot $gribfile pwat 19 2 $timee&
	plot $gribfile cape 17 200 $timee&
	wait
	
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

for i in $times
do
	if [[ "$i" == "0" || "$i" == "3" || "$i" == "6" || "$i" == "9" ]]
	then
		i="0$i"
	fi
	
	time doplot $datee $run $i
done

#cleanup

if [ -d "$tmp" ]
then
        rm -r "$tmp"
fi

