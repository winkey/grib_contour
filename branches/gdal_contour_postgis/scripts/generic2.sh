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

source /etc/profile
source ~/.profile

export PATH="$PATH:/usr/local/bin"

script=$(basename ${0})

if [ "$2" == "" ]
then
	datee=`date -u "+%Y%m%d"`
else
	datee=$2
fi

##### get the number of cpu's #####

cpus=$(cat /proc/cpuinfo | grep "^processor" | wc -l)

################################################################################
#
# function to proccess a list of jobs
#
# 

function do_jobs {

	for job in "${joblist[@]}"
	do
		while [[ $(jobs | wc -l) -ge $cpus ]]
		do
			sleep 2
		done
	
		$job &
	done

}
	
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
	
	cat > $frames << EOF
<?xml version="1.0" encoding="UTF-8"?>
<kml xmlns="http://earth.google.com/kml/2.2">
<Folder>
  <ScreenOverlay>
    <name>Key</name>
    <visibility>1</visibility>
		<Icon>
      <href>${www}/../images/${name}.png</href>
    </Icon>
    <overlayXY x="0" y="1" xunits="fraction" yunits="fraction"/>
    <screenXY x="0" y="1" xunits="fraction" yunits="fraction"/>
    <rotationXY x="0" y="0" xunits="fraction" yunits="fraction"/>
    <size x="0" y="0" xunits="fraction" yunits="fraction"/>
  </ScreenOverlay>
  <name>frames</name>
    <description></description>
</Folder>
</kml>
EOF

	##### check the latest link #####
	
	if [ -h "${wwwdisk}/latest" ]
	then
		rm ${wwwdisk}/latest
	fi

	ln -s "${wwwdisk}/${run}" -T "${wwwdisk}/latest"	


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
	incr=$3
	grid=$4
	
	tmpfile=/tmp/$script.$run.$name.kml
	frames=${wwwdisk}/${run}/${name}.kml
	lock="/tmp/$script.$run.$name.lock"
	
	if [[ "$grid" != "" ]]
	then
		zip="${www}/${run}/${grid}.${name}${hr}.kmz"
	else
		zip="${www}/${run}/${name}${hr}.kmz"
	fi

	##### lock the file #####
	
	while ! mkdir "$lock"
	do
		sleep 1
	done
	
	head -n -2 $frames > $tmpfile

	begin=`date -d "$run GMT $hr hours" "+%FT%TZ" -u`
	end=`date -d "$run GMT $hr hours $incr hours" "+%FT%TZ" -u`

cat >> $tmpfile << EOF
  <NetworkLink>
    <name>${run}Z + ${hr} ${grid}.${name}</name>
    <TimeSpan>
      <begin>${begin}</begin>
      <end>${end}</end>
    </TimeSpan>
    <visibility>1</visibility>
    <open>0</open>
    <Url>
      <href>${zip}</href>
    </Url>
  </NetworkLink>
EOF

	tail -n 2 $frames >> $tmpfile
	mv $tmpfile $frames
	
	##### remove the lock #####
	
	rmdir "$lock"

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
	incr=$6
	extra="$7"

	zip="${wwwdisk}/${run}/${name}${timee}.kmz"
	kml="${name}${timee}.kml"
	
	if [[ -f "$zip" ]]
	then
		rm "$zip"
	fi
	
	nice -n 10 grib_contour -g "${gribfile}" -m $grbmsg \
													-i $interval -s $name \
													-k $kml -z "$zip" \
													$extra
	
	appendkml $name $timee $incr $grid
	
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
	ufile="$1"
	vfile="$2"
	name="$3"
	umsg=$4
	vmsg=$5
	interval=$6
	timee=$7
	incr=$8
	extra="$7"

	zip="${wwwdisk}/${run}/${name}${timee}.kmz"
	kml="${name}${timee}.kml"
	
	if [[ -f "$zip" ]]
	then
		rm "$zip"
	fi
	
	nice -n 10 grib_contour -w -u "${ufile}" -v "${vfile}" \
													-U $umsg -V $vmsg \
													-i $interval -s $name \
													-k $kml -z "$zip" \
													$extra
	
	appendkml $name $timee $incr $grid
	
}

function andplot {
	ufile="$1"
	vfile="$2"
	name="$3"
	umsg=$4
	vmsg=$5
	interval=$6
	timee=$7
	incr=$8
	extra="$7"
	
	zip="${wwwdisk}/${run}/${name}${timee}.kmz"
	kml="${name}${timee}.kml"
	
	if [[ -f "$zip" ]]
	then
		rm "$zip"
	fi
	
	nice -n 10 grib_contour -a -u "${ufile}" -v "${vfile}" \
													-U $umsg -V $vmsg \
													-i $interval -s $name \
													-k $kml -z "$zip" \
													$extra
	
	appendkml $name $timee $incr $grid
	
}

function diffplot {
	ufile="$1"
	vfile="$2"
	name="$3"
	umsg=$4
	vmsg=$5
	interval=$6
	timee=$7
	incr=$8
	extra="$9"
	
	zip="${wwwdisk}/${run}/${name}${timee}.kmz"
	kml="${name}${timee}.kml"
	
	if [[ -f "$zip" ]]
	then
		rm "$zip"
	fi
	
	nice -n 10 grib_contour -d -u "${ufile}" -v "${vfile}" \
													-U $umsg -V $vmsg \
													-i $interval -s $name \
													-k $kml -z "$zip" \
													$extra
	
	appendkml $name $timee $incr $grid
	
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
	ddir=$3
	
	wget "${dir}${file}" -O "${ddir}/${file}"
}

