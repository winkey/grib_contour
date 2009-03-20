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

fwtools="/home/winkey/FWTools-1.3.2/bin_safe/"
serv="ftp://ftpprd.ncep.noaa.gov/pub/data/nccf/com/gfs/prod/"
servb="http://www.ftp.ncep.noaa.gov/data/nccf/com/gfs/prod/"
wwwdisk="/var/www/apache2-default/weather/kml/gfs"
www="http://hypercube.telascience.org/weather/kml/gfs"

times=`seq 0 3 180`





################################################################################
#	function to fetch the grib file
#
#	args:
#					$1	the date of the run (GMT)
#					$2	the model run
#					$3	the forcast hour in the run
################################################################################

function getgrib_curl {
	datee=$1
	run=$2
	timee=$3
	
	fil="gfs.t${run}z.pgrb2f${timee}"
	idx="gfs.t${run}z.pgrb2f${timee}.idx"
	
	get_inv.pl "${servb}gfs.${datee}${run}/${idx}" |\
	 grep -e ":HGT:\(925\|850\|700\|500\|300\) mb:\|TMP:\(925\|850\|700\|500\|300\) mb:\|RH:\(925\|850\|700\|500\|300\) mb:\|UGRD:\(925\|850\|700\|500\|300\) mb:\|VGRD:\(925\|850\|700\|500\|300\) mb:\|PWAT" |\
	 get_grib.pl "${servb}gfs.${datee}${run}/${fil}" "${tmp}/${fil}"
}


function doplot {
	datee=$1
	run=$2
	timee=$3
	
	gribfile="gfs.t${run}z.pgrb2f${timee}"
	
	if ! getgrib_curl "$datee" "$run" "$timee"
	then
		return
	fi
		
	plot $gribfile 925hgt 17 20 $timee&
	plot $gribfile 925t 18 1 $timee&
	plot $gribfile 925rh 19 5 $timee&
	windplot $gribfile 925wind 20 10 $timee&
	wait
	
	plot $gribfile 850hgt 13 20 $timee&
	plot $gribfile 850t 14 1 $timee&
	plot $gribfile 850rh 15 5 $timee&
	windplot $gribfile 850wind 16 10 $timee&
	wait

	plot $gribfile 700hgt 9 20 $timee&
	plot $gribfile 700t 10 1 $timee&
	plot $gribfile 700rh 11 5 $timee&
	windplot $gribfile 700wind 12 10 $timee&
	wait

	plot $gribfile 500hgt 5 20 $timee&
	plot $gribfile 500t 6 1 $timee&
	plot $gribfile 500rh 7 5 $timee&
	windplot $gribfile 500wind 8 10 $timee&
	wait

	plot $gribfile 300hgt 1 20 $timee&
	plot $gribfile 300t 2 1 $timee&
	plot $gribfile 300rh 3 5 $timee&
	windplot $gribfile 300wind 4 10 $timee&
	
	wait
	plot $gribfile pwat 21 1 $timee
	plot $gribfile cape 191 50 $timee
	
	#cleanup
	
	rm "${tmp}/*"
	
}

mktempfiledir "$tmp"
cd "$fwtools"

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
