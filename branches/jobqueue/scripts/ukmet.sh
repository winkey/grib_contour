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

wwwdisk="/home/rush/winkey/public_html//kml/ukmet"
www="atmos.ucsd.edu//kml/ukmet"



path="$1"
grid="$2"
datee="$3"
run="$4"
hour="${5#0}"
prod="$6"
level="$7"
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

if [[ "$prod" == "HGT" ]]
then
	
	unset paths i
	for grid in 037 038 039 040 041 042 043 044
	do
		tpath=$(echo "$path" | sed s:/0[3-4][0-9][.]:/$grid.:)
		if [[ -f "$tpath" ]]
		then
			paths[i++]="-g"
			paths[i++]="$tpath"
		fi
	done
	
	if [[ "$i" == "16" ]]
	then
		zip="${wwwdisk}/${run}/${level}hgt${hour}.kmz"
		kml="${level}hgt${hour}.kml"
	
		if [[ -f "$zip" ]]
		then
			rm "$zip"
		fi
		
		nice -n 10 grib_contour "${paths[@]}" -i 20 -s ${level}hgt -q "lin,dlat=2.5,dlon=2.5" -k "$kml" -z "$zip" "-H"

		if [[ "$hour" == "06" ]]
		then
			mkrootkml "${level}hgt"
		fi
		appendkml ${level}hgt $hour 06
	fi
fi

##### plot temp #####

if [[ "$prod" == "TMP" ]]
then
	if [[ "$hour" == "06" ]]
	then
		mkrootkml "${level}t"
	fi
	
	unset paths i
	for grid in 037 038 039 040 041 042 043 044
	do
		tpath=$(echo "$path" | sed s:/0[3-4][0-9][.]:/$grid.:)
		if [[ -f "$tpath" ]]
		then
			paths[i++]="-g"
			paths[i++]="$tpath"
		fi
	done
	
	if [[ "$i" == "16" ]]
	then
		zip="${wwwdisk}/${run}/${level}t${hour}.kmz"
		kml="${level}t${hour}.kml"
	
		if [[ -f "$zip" ]]
		then
			rm "$zip"
		fi
		
		nice -n 10 grib_contour "${paths[@]}" -i 1 -s ${level}t -c -273.15 -q "lin,dlat=2.5,dlon=2.5" -k "$kml" -z "$zip"

		appendkml ${level}t $hour 06
	fi
fi

##### plot rh #####

if [[ "$prod" == "RH" ]]
then
	
	unset paths i
	for grid in 037 038 039 040 041 042 043 044
	do
		tpath=$(echo "$path" | sed s:/0[3-4][0-9][.]:/$grid.:)
		if [[ -f "$tpath" ]]
		then
			paths[i++]="-g"
			paths[i++]="$tpath"
		fi
	done
	
	if [[ "$i" == "16" ]]
	then
		zip="${wwwdisk}/${run}/${level}rh${hour}.kmz"
		kml="${level}rh${hour}.kml"
	
		if [[ -f "$zip" ]]
		then
			rm "$zip"
		fi
		
		nice -n 10 grib_contour "${paths[@]}" -i 5 -s ${level}rh -q "lin,dlat=2.5,dlon=2.5" -k "$kml" -z "$zip"

		if [[ "$hour" == "06" ]]
		then
			mkrootkml "${level}rh"
		fi
		appendkml ${level}rh $hour 06
	fi
fi

##### wind #####

if [[ "$prod" == "UGRD" ]]
then
	vpath=$(echo "$path" | sed s/UGRD/VGRD/)
	
	unset paths i
	for grid in 037 038 039 040 041 042 043 044
	do
		tpath=$(echo "$path" | sed s:/0[3-4][0-9][.]:/$grid.:)
		if [[ -f "$tpath" ]]
		then
			paths[i++]="-u"
			paths[i++]="$tpath"
		fi
	done
	for grid in 037 038 039 040 041 042 043 044
	do
		tpath=$(echo "$vpath" | sed s:/0[3-4][0-9][.]:/$grid.:)
		if [[ -f "$tpath" ]]
		then
			paths[i++]="-v"
			paths[i++]="$tpath"
		fi
	done
		
	if [[ "$i" == "32" ]]
	then
		zip="${wwwdisk}/${run}/${level}wind${hour}.kmz"
		kml="${level}wind${hour}.kml"
	
		if [[ -f "$zip" ]]
		then
			rm "$zip"
		fi
		
		if [[ "$level" -gt "500" ]]
		then
			interval=5
		else
			interval=7
		fi
		
		nice -n 10 grib_contour -w "${paths[@]}" -i $interval -s ${level}wind -q "lin,dlat=2.5,dlon=2.5" -k "$kml" -z "$zip"

		if [[ "$hour" == "06" ]]
		then
			mkrootkml "${level}wind"
		fi
	
		appendkml ${level}wind $hour 06
	fi
fi

if [[ "$prod" == "VGRD" ]]
then
	upath=$(echo "$path" | sed s/VGRD/UGRD/)
	
	unset paths i
	for grid in 037 038 039 040 041 042 043 044
	do
		tpath=$(echo "$path" | sed s:/0[3-4][0-9][.]:/$grid.:)
		if [[ -f "$tpath" ]]
		then
			paths[i++]="-v"
			paths[i++]="$tpath"
		fi
	done
	for grid in 037 038 039 040 041 042 043 044
	do
		tpath=$(echo "$upath" | sed s:/0[3-4][0-9][.]:/$grid.:)
		if [[ -f "$tpath" ]]
		then
			paths[i++]="-u"
			paths[i++]="$tpath"
		fi
	done
		
	if [[ "$i" == "32" ]]
	then
		zip="${wwwdisk}/${run}/${level}wind${hour}.kmz"
		kml="${level}wind${hour}.kml"
	
		if [[ -f "$zip" ]]
		then
			rm "$zip"
		fi
		
		if [[ "$level" -gt "500" ]]
		then
			interval=5
		else
			interval=7
		fi
		
		nice -n 10 grib_contour -w "${paths[@]}" -i $interval -s ${level}wind -q "lin,dlat=2.5,dlon=2.5" -k "$kml" -z "$zip"

		if [[ "$hour" == "06" ]]
		then
			mkrootkml "${level}wind"
		fi

		appendkml ${level}wind $hour 06
	fi
fi

#### plot pmsl #####

if [[ "$prod" == "PRMSL" ]]
then
	unset paths i
	for g in 037 038 039 040 041 042 043 044
	do
		tpath=$(echo "$path" | sed s:/0[3-4][0-9][.]:/$grid.:)
		if [[ -f "$tpath" ]]
		then
			paths[i++]="-g"
			paths[i++]="$tpath"
		fi
	done
	
	if [[ "$i" == "16" ]]
	then
		zip="${wwwdisk}/${run}/pmsl${hour}.kmz"
		kml="pmsl${hour}.kml"
	
		if [[ -f "$zip" ]]
		then
			rm "$zip"
		fi
		
		echo nice -n 10 grib_contour "${paths[@]}" -i 200 -s pmsl -q "lin,dlat=2.5,dlon=2.5" -k "$kml" -z "$zip"
		nice -n 10 grib_contour "${paths[@]}" -i 200 -s pmsl -q "lin,dlat=2.5,dlon=2.5" -k "$kml" -z "$zip" "-H"

		if [[ "$hour" == "06" ]]
		then
			mkrootkml "pmsl"
		fi
	
		appendkml pmsl $hour 06
	fi
fi



