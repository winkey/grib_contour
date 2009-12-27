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
wwwbase="atmos.ucsd.edu//kml"
wwwdiskbase="/home/rush/winkey/public_html//kml"

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
	
	frames="$wwwdiskbase/$model/$run/$name.kml"
	
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
	
	if [ -h "$wwwdiskbase/$model/latest" ]
	then
		rm $wwwdiskbase/$model/latest
	fi

	ln -s "$wwwdiskbase/$model/${run}" -T "$wwwdiskbase/$model/latest"	


}

################################################################################
#	function to append the new frame to the root kml
#
################################################################################

function appendkml {
	name=$1
	hr=$2
	incr=$3
	run=$4
	wwwzip="$5"
	frames="$6"
	
	lock="/tmp/${frames//\//.}.lock"
	
	begin=$(date -d "$run GMT $hr hours" "+%FT%TZ" -u)
	end=$(date -d "$run GMT $hr hours $incr hours" "+%FT%TZ" -u)

	##### lock the file #####
	
	while ! mkdir "$lock"
	do
		sleep 1
	done
	
	
ed -s $frames << EOF
$ -2a
  <NetworkLink>
    <name>${run}Z + ${hr} ${grid}.${name}</name>
    <TimeSpan>
      <begin>${begin}</begin>
      <end>${end}</end>
    </TimeSpan>
    <visibility>1</visibility>
    <open>0</open>
    <Url>
      <href>${wwwzip}</href>
    </Url>
  </NetworkLink>
.
w
EOF

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

export npipe="$HOME/jobqueue.pipe"
export lock="$HOME/jobqueue.lock"
export maxload=50
export maxjobs=30

################################################################################
# function to fetch a cmd from the pipe
################################################################################

function readfifo {
  
  ret=1
  i=0
  
  while IFS=$'\0' read -t 1 -r -d '' param <"$npipe" && \
        ret=$? && \
        [[ $param != $'\n' ]]
  do
    cmd[i++]="$param"
  done
  
  return $ret
}

################################################################################
# main loop jobqueue function
################################################################################

function mainloop {
  
  ##### loop while there is a cmd in the pipe or we have bg jobs #####
  
  while readfifo && r=$? || (( $(jobs -r | wc -l) ))
  do
    
    ##### loop and sleep if we are too busy #####
    
    while read l junk </proc/loadavg ; (( ${l%%.*} > $maxload )) ||\
          (( $(jobs -r | wc -l) > $maxjobs ))
    do 
      sleep 5
    done
    
    ##### run the queued command #####
    
    if ! (( $r ))
    then
      (eval "${cmd[@]}") &
    fi
    
    unset cmd
    
    r=1
    
  done
  
  ##### remove the lock file were exiting #####
  
  rmdir "$lock"
}

################################################################################
# function to add a job to the job queue
################################################################################

function enqueue {

  ##### if the pipe don't exist create it #####

  if ! [[ -p "$npipe" ]]
  then
    mkfifo "$npipe"
    chmod 600 "$npipe"
  fi
  
  ##### open the pipe to a fd RW #####
  
  exec 3<>"$npipe"
  
  ##### send the command followed by a \n to the pipe #####
  
  printf "%s\0" "$@" $'\n' >&3
  
  ##### close the pipe #####
  
  #exec 3>&-
  
  ##### if there is no lock file make it and start the main loop #####

  if mkdir "$lock" >/dev/null 2>&1
  then
    (
      mainloop >/dev/null 2>&1 &
      disown
    )
    
  fi
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
	frames=${wwwdisk}/${run}/${name}.kml
	wwwzip="${www}/${run}/${name}${timee}.kmz"
	
	if [[ -f "$zip" ]]
	then
		rm "$zip"
	fi
	
	enqueue nice -n 10 grib_contour -g "${gribfile}" -m $grbmsg \
													-i $interval -s $name \
													-k $kml -z "$zip" \
													$extra \
	\;\
	appendkml $name $timee $incr $run $wwwzip $frames
	
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
	frames=${wwwdisk}/${run}/${name}.kml
	wwwzip="${www}/${run}/${name}${timee}.kmz"
	
	if [[ -f "$zip" ]]
	then
		rm "$zip"
	fi
	
	enqueue nice -n 10 grib_contour -w -u "${ufile}" -v "${vfile}" \
													-U $umsg -V $vmsg \
													-i $interval -s $name \
													-k $kml -z "$zip" \
													$extra \
	\;\
	appendkml $name $timee $incr $run $wwwzip
	
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
	frames=${wwwdisk}/${run}/${name}.kml
	wwwzip="${www}/${run}/${name}${timee}.kmz"
	
	if [[ -f "$zip" ]]
	then
		rm "$zip"
	fi
	
	enqueue nice -n 10 grib_contour -a -u "${ufile}" -v "${vfile}" \
													-U $umsg -V $vmsg \
													-i $interval -s $name \
													-k $kml -z "$zip" \
													$extra \
	\;\
	appendkml $name $timee $incr $run $wwwzip $frames
	
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
	frames=${wwwdisk}/${run}/${name}.kml
	wwwzip="${www}/${run}/${name}${timee}.kmz"
	
	if [[ -f "$zip" ]]
	then
		rm "$zip"
	fi
	
  enqueue nice -n 10 grib_contour -d -u "${ufile}" -v "${vfile}" \
													-U $umsg -V $vmsg \
													-i $interval -s $name \
													-k $kml -z "$zip" \
													$extra \
	\;\
	appendkml $name $timee $incr $run $wwwzip $frames
	
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
