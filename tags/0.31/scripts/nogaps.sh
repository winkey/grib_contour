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

serv="ftp://ftpprd.ncep.noaa.gov/pub/data/nccf/com/nam/prod/"
servb="http://www.ftp.ncep.noaa.gov/data/nccf_backup/pub/data/model/grid/grib/nogaps/"
wwwdisk="/home/rush/public_html/weather/kml/nogaps"
www="http://atmos.ucsd.edu/kml/nogaps/"


run=$1

times="$(seq -f "%03g" 0 3 24) $(seq -f "%03g" 30 6 84) $(seq -f "%03g" 96 12 144)"

if ! [[ -d "${wwwdisk}/${run}" ]]
then
	mkdir -p "${wwwdisk}/${run}"
fi

function doplot {
	datee=$1
	run=$2
	timee=$3
	
	gribfile="nogaps_${datee}${run}f${timee}"
	if ! getgrib "${servb}" "$gribfile" "/tmp"
	then
		return
	fi
	
	gribfile="/tmp/${gribfile}"
  
	if [[ $((10#$timee)) -lt 24 ]]
	then
		incr=3
	else
		if [[ $((10#$timee)) -lt 84 ]]
		then
			incr=6
		else
			incr=12
		fi
	fi
	
	function sgrib {
		grep <(echo "$gribindex") -e "$1" | cut -d "," -f 1
	}

	gribindex=$(degrib $gribfile -I | cut -d "," -f 1,4-5 | sed 's/=".*"//')
	
	plot $gribfile 1000hgt $(sgrib "HGT, 1000-ISBL") 20 $timee $incr &
	plot $gribfile 1000t $(sgrib "TMP, 1000-ISBL") 1 $timee $incr &
	plot $gribfile 1000rh $(sgrib "RH, 1000-ISBL") .1 $timee $incr "-S 0.01" &
	windplot $gribfile $gribfile 1000wind $(sgrib "UGRD, 1000-ISBL") $(sgrib "VGRD, 1000-ISBL") 5 $timee $incr &
	wait

	plot $gribfile 925hgt $(sgrib "HGT, 925-ISBL") 20 $timee $incr &
	diffplot $gribfile $gribfile 925thk $(sgrib "HGT, 925-ISBL") $(sgrib "TMP, 1000-ISBL") 20 $timee $incr &
	wait
	windplot $gribfile $gribfile 925wind $(sgrib "UGRD, 925-ISBL") $(sgrib "VGRD, 925-ISBL") 5 $timee $incr &
	
	plot $gribfile 850hgt $(sgrib "HGT, 850-ISBL") 20 $timee $incr &
	wait
	plot $gribfile 850t $(sgrib "TMP, 850-ISBL") 1 $timee $incr &
	plot $gribfile 850rh $(sgrib "RH, 850-ISBL") .1 $timee $incr "-S 0.01" &
	wait
	diffplot $gribfile $gribfile 850thk $(sgrib "HGT, 850-ISBL") $(sgrib "TMP, 1000-ISBL") 20 $timee $incr &
	windplot $gribfile $gribfile 850wind $(sgrib "UGRD, 850-ISBL") $(sgrib "VGRD, 850-ISBL") 5 $timee $incr &
	wait

	plot $gribfile 700hgt $(sgrib "HGT, 700-ISBL") 20 $timee $incr &
	plot $gribfile 700t $(sgrib "TMP, 700-ISBL") 1 $timee $incr &
	wait
	plot $gribfile 700rh $(sgrib "RH, 700-ISBL") .1 $timee $incr "-S 0.01" &
	diffplot $gribfile $gribfile 700thk $(sgrib "HGT, 700-ISBL") $(sgrib "TMP, 1000-ISBL") 20 $timee $incr &
	wait
	windplot $gribfile $gribfile 700wind $(sgrib "UGRD, 700-ISBL") $(sgrib "VGRD, 700-ISBL") 5 $timee $incr &
	
	plot $gribfile 500hgt $(sgrib "HGT, 500-ISBL") 20 $timee $incr &
	wait
	plot $gribfile 500t $(sgrib "TMP, 500-ISBL") 1 $timee $incr &
	plot $gribfile 500rh $(sgrib "RH, 500-ISBL") .1 $timee $incr "-S 0.01" &
	wait
	diffplot $gribfile $gribfile 500thk $(sgrib "HGT, 500-ISBL") $(sgrib "TMP, 1000-ISBL") 20 $timee $incr &
	windplot $gribfile $gribfile 500wind $(sgrib "UGRD, 500-ISBL") $(sgrib "VGRD, 500-ISBL") 10 $timee $incr &
	wait

	plot $gribfile 300hgt $(sgrib "HGT, 300-ISBL") 20 $timee $incr &
	plot $gribfile 300t $(sgrib "TMP, 300-ISBL") 1 $timee $incr &
	wait
	plot $gribfile 300rh $(sgrib "RH, 300-ISBL") .1 $timee $incr "-S 0.01" &
	windplot $gribfile $gribfile 300wind $(sgrib "UGRD, 300-ISBL") $(sgrib "VGRD, 300-ISBL") 10 $timee $incr &
	wait
	
	plot $gribfile 200hgt $(sgrib "HGT, 200-ISBL") 20 $timee $incr &
	plot $gribfile 200t $(sgrib "TMP, 200-ISBL") 1 $timee $incr &
	wait
	plot $gribfile 200rh $(sgrib "RH, 200-ISBL") .1 $timee $incr "-S 0.01" &
	windplot $gribfile $gribfile 200wind $(sgrib "UGRD, 200-ISBL") $(sgrib "VGRD, 200-ISBL") 10 $timee $incr &
	wait
	
	plot $gribfile pmsl $(sgrib "HGT, 300-ISBL") 200 $timee $incr &
	if [[ "$timee" != "000" ]]
	then
		plot $gribfile pcp 2 1 $timee $incr "-I" &
	fi
	wait
	

	#cleanup
	
	rm "${gribfile}"
	
}

mktempfiledir "$tmp"

mkrootkml 1000hgt
mkrootkml 1000t
mkrootkml 1000rh
mkrootkml 1000wind

mkrootkml 925hgt
mkrootkml 925thk
mkrootkml 925wind

mkrootkml 850hgt
mkrootkml 850t
mkrootkml 85thk
mkrootkml 850rh
mkrootkml 850wind

mkrootkml 700hgt
mkrootkml 700t
mkrootkml 700thk
mkrootkml 700rh
mkrootkml 700wind

mkrootkml 500hgt
mkrootkml 500t
mkrootkml 500thk
mkrootkml 500rh
mkrootkml 500wind

mkrootkml 300hgt
mkrootkml 300t
mkrootkml 300rh
mkrootkml 300wind

mkrootkml 200hgt
mkrootkml 200t
mkrootkml 200rh
mkrootkml 200wind

mkrootkml pmsl


for i in $times
do
	time doplot $datee $run $i
done

#cleanup


