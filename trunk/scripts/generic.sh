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

source /etc/profile
source ~/.profile

export LD_LIBRARY_PATH="/home/winkey/lib/:${LD_LIBRARY_PATH}"



if [ "$2" == "" ]
then
	datee=`date -u "+%Y%m%d"`
else
	datee=$2
fi

run=$1
tmp="/tmp/$(basename ${0}).$run"

################################################################################
#	function to make a dir for the temporary files
#
#	args:
#					$1	the dir to create
################################################################################

function mktempfiledir {
	if [ -d "$1" ]
	then
		rm -r "$1"
	else
		mkdir "$1"
	fi
}

################################################################################
#	function to create the root kml file
#
#	args:
#					$1	the name of the product ie: 925hgt
################################################################################

function mkrootkml {
	name=$1
	
	frames=${wwwdisk}/${run}/${name}.kml
	
	echo '<?xml version="1.0" encoding="UTF-8"?>' > $frames
	echo '<kml xmlns="http://earth.google.com/kml/2.2">' >> $frames
	echo '<Folder>' >> $frames
	echo '	<ScreenOverlay>' >> $frames
  echo '		<name>Key</name>' >> $frames
  echo '		<visibility>1</visibility>' >> $frames
  echo '		<Icon>' >> $frames
  echo "			<href>${www}/../images/${name}.png</href>" >> $frames
  echo '		</Icon>' >> $frames
  echo '		<overlayXY x="0" y="1" xunits="fraction" yunits="fraction"/>' >> $frames
  echo '		<screenXY x="0" y="1" xunits="fraction" yunits="fraction"/>' >> $frames
  echo '		<rotationXY x="0" y="0" xunits="fraction" yunits="fraction"/>' >> $frames
  echo '		<size x="0" y="0" xunits="fraction" yunits="fraction"/>' >> $frames
  echo '	</ScreenOverlay>' >> $frames

	echo '  <name>frames</name>' >> $frames
	echo '  <description></description>' >> $frames
	echo '</Folder>' >> $frames
	echo '</kml>' >> $frames
}

################################################################################
#	function to append the new frame to the root kml
#
#	args:
#					$1	name ie: 925hgt etc...
#					$2	the forcast hour in the run
#					
################################################################################

function appendkml {
	name=$1
	hr=$2

	tmpfile=${tmp}/${name}.kml
	frames=${wwwdisk}/${run}/${name}.kml

	head -n -2 $frames > $tmpfile

	begin=`date -d "$run GMT $hr hours" "+%FT%TZ" -u`
	end=`date -d "$run GMT $hr hours 03 hours" "+%FT%TZ" -u`

	echo '  <NetworkLink>' >> $tmpfile
	echo "    <name>${run}Z + ${hr} ${name}</name>" >> $tmpfile
	echo '    <TimeSpan>' >> $tmpfile
	echo "      <begin>${begin}</begin>" >> $tmpfile
	echo "      <end>${end}</end>" >> $tmpfile
	echo '    </TimeSpan>' >> $tmpfile
	echo '    <visibility>1</visibility>' >> $tmpfile
	echo '    <open>0</open>' >> $tmpfile
	echo '    <Url>' >> $tmpfile
	echo "      <href>${www}/${run}/${name}${hr}.kmz</href>" >> $tmpfile
	echo '    </Url>' >> $tmpfile
	echo '  </NetworkLink>' >> $tmpfile

	tail -n 2 $frames >> $tmpfile
	mv $tmpfile $frames

}

################################################################################
#	function to make a fifo
#
#	args:
#					$1	the filename of the fifo
#
################################################################################

function my_mkfifo {
	if [ -p "$1" ]
	then 
		rm "$1"
	fi
	mknod "$1" p
}

################################################################################
#	function to plot the data
#
#	args:
#					$1	the grib file to plot
#					$2	the name of the product ie: 925hgt
#					$3	the grib msg #
#					$4	interval apart the contours are
#					$5	the forcast hour in the run
################################################################################

function plot {
	gribfile=$1
	name="$2"
	grbmsg=$3
	interval=$4
	timee=$5
	
	zip="${wwwdisk}/${run}/${name}${timee}.kmz"
	kml="${name}${timee}.kml"
	
	if [[ -f "$zip" ]]
	then
		rm "$zip"
	fi
	
	grib_contour -g "${tmp}/${gribfile}" -m $grbmsg -i $interval -s $name -k $kml -z "$zip"
	
	appendkml $name $timee
	
}

################################################################################
#  function to plot the wind data
#
#	 args:
#					$1	the grib file to plot
#					$2	the name of the product ie: 925hgt
#					$3	the grib msg #
#					$4	interval apart the contours are
#					$5	the forcast hour in the run
################################################################################

function windplot {
	ufile=$1
	vfile=$2
	name="$3"
	umsg=$4
	vmsg=$5
	interval=$6
	timee=$7
	
	
	zip="${wwwdisk}/${run}/${name}${timee}.kmz"
	kml="${name}${timee}.kml"
	
	if [[ -f "$zip" ]]
	then
		rm "$zip"
	fi
	
	grib_contour -w -u "${ufile}" -v "${ufile}" -U $umsg -V $vmsg -i $interval -s $name -k $kml -z "$zip"
	
	appendkml $name $timee


}

################################################################################
#	function to fetch the grib file
#
#	args:
#					$1	the site and path
#					$2	the filename
################################################################################

function getgrib {
	dir=$1
	file=$2
	
	wget "${dir}${file}" -O "${tmp}/${file}"
}
