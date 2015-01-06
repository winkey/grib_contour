#!/bin/bash


# Copyright (c) 2010-2014, Brian Case
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included
# in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
# OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
# THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
# DEALINGS IN THE SOFTWARE.


# the code to start multiple jobs came from opengdp under the above licence
# ps if anybody wants to complain, i wrote it all, its my code i will mix it if i want ;-)

## @param indir                   dir the original file(s) will be placed in
## @param outdir                  dir to place the output in

name="gfs"
dsname="$name"
datadir="/bigdata/coldwave"
indir="/bigdata/coldwave/source"
outdir="/bigdata/coldwave/done"
baseurl="ftp://nomads.ncdc.noaa.gov/GFS/Grid4"
tmp="/tmp"



limit=14

start=20141020
  end=20141131



main() {

    mkdir -p "${indir}/${dsname}"
    mkdir -p "${outdir}/${dsname}"
    
    getlist "$start" "$end" > "${indir}/${dsname}/mirrorfile" 
    mainloop "${indir}/${dsname}/mirrorfile"
   

}


getlist() {
    local start="$1"
    local end="$2"
    
    local yyyymm
    local run
    local hour

    local yyyymmdd="$start"
    while [ "$yyyymmdd" -le "$end" ]
    do


        yyyymmdd=$(date -d "$yyyymmdd + 1 days" "+%Y%m%d")
        yyyymm=$(date -d "$yyyymmdd" "+%Y%m")
       

        echo "mkdir file:${indir}/${yyyymmdd}"
        echo "chmod 755 file:${indir}/${yyyymmdd}"

        ##### loop over the runs #####

        for run in 0000 0600 1200 1800
        do
            
            ##### loop over the hours #####

            for hour in 000 003
            do
                if ! [ -f "${indir}/${yyyymmdd}/gfs_4_${yyyymmdd}_${run}_${hour}.grb2" ]
                then
                    echo "get -O ${indir}/${yyyymmdd} ${baseurl}/${yyyymm}/${yyyymmdd}/gfs_4_${yyyymmdd}_${run}_${hour}.grb2"
                    echo "chmod 644 file:${indir}/${yyyymmdd}/gfs_4_${yyyymmdd}_${run}_${hour}.grb2"
                fi
            done
        done
    done
}

###############################################################################
## @brief frontend to bc for calcing floats
##
## @param ...   the calculation to perform
##
## @return 0 for success, 1 for failure
## 
## @retval stdout the calculation result
##
###############################################################################

fcalc () {

    if [[ $# -gt 0 ]]
    then
        bc -q 2>/dev/null <<< "scale=20; $*"
    fi
}

###############################################################################
## @brief print est completion time meter to stdout
##
## @param started    time job started UNIXTIME
## @param lines      total number of jobs
## @param donelines  jobs completed
##
## @return 0 for success
##
###############################################################################

comp_meter () {
    started=$1
    lines=$2
    donelines=$3
    
    local comp
    local decdone=$(fcalc "$donelines / $lines")
    local percdone=$(fcalc "scale = 0; $decdone * 100")
    local elap=$(($(date +%s) - started))
    local comp=$(fcalc "scale=0; $elap / $decdone")
    ((comp +=  started))
    
    printf "\r%3.0f%% complete. EST. finish at %s" $percdone "$(date -d "@${comp}")"
}

###############################################################################
## @brief function to spawn a new job
##
###############################################################################


startjob() {
    local line="$line"
    
    dofile "$line"  &
        
}

###############################################################################
## @brief multi proceessing loop
##
## @param mirrorfile     the mirror file
##
## @return 0 for success
##
###############################################################################

mainloop () {
    local mirrorfile="$1"

    local doing
    local line
    local lines
    local donelines
    local started

    ((doing=0))
    
    ##### open a fd to a named pipe #####

    mkfifo pipe; exec 3<>pipe
    
    ##### setup for the est completion time #####
    
    lines=$(grep "${mirrorfile}" -e "^get" | wc -l  | cut -d " " -f 1 )
    ((donelines=0))
    started=$(date +%s)
    
    ##### loop over the list #####

    while read line ;
    do
        
        ##### if it is a mkdir command do it now #####
        
        if grep -e "^mkdir" <<< "$line" > /dev/null
        then
            lftp -e "$line ; exit"
            continue
        fi
        
        ##### under the limit just start a job #####

        if [ $doing -lt $limit ]
        then
        	startjob "$line"
         	((doing++))
         	
        ##### over the limit wait for a job to finish before starting #####
        
        else
            read <&3
            ((doing--))
            
            if grep -e "^get" <<< "$line" > /dev/null
            then
                ((donelines++))
            fi

            comp_meter $started $lines $donelines
            
            startjob "$line"
         	((doing++))
        fi

    done < "${mirrorfile}"

    wait

    echo

}



getdate() {
    sed 's:.*gfs_4_\([0-9]\{4\}\)\([0-9]\{2\}\)\([0-9]\{2\}\)_\([0-9]\{2\}\)00_0\([0-9]\{2\}\).*:\1\2\3:'

}

getrun() {

    sed 's:.*gfs_4_\([0-9]\{4\}\)\([0-9]\{2\}\)\([0-9]\{2\}\)_\([0-9]\{2\}\)00_0\([0-9]\{2\}\).*:\4:'

}

gethour() {

    sed 's:.*gfs_4_\([0-9]\{4\}\)\([0-9]\{2\}\)\([0-9]\{2\}\)_\([0-9]\{2\}\)00_0\([0-9]\{2\}\).*:\5:'

}

subtmplftp() {\
    local tmpdir="$1"

    sed "s:get \([-]. \)\{1,\}[-/_.A-Za-z0-9]*:get \1${tmpdir}:g"
}
###############################################################################
## @brief function to get the basename of a file
##
## @param input     pathname to parse
##
## @return 0 on success
## @retval stdout the basename
##
###############################################################################

file_get_basename () {
    local input="$1"
    
    local file="${input##*/}"
    
    local base="${file%.*}"
    local base2="${base%.*}"
    local ext="${file##*.}"
    local ext2="${base##*.}"
    local ext=$(tr "[A-Z]" "[a-z]" <<< "$ext")
    local ext2=$(tr "[A-Z]" "[a-z]" <<< "$ext2")

    if [[ "$ext2" == "tar" ]]
    then
        ext="${ext2}.${ext}"
        base="$base2"
    fi
    
    echo "$base"
    
}

###############################################################################
## @brief function to get the extension of a file
##
## @param input     pathname to parse
##
## @return 0 on success
## @retval stdout the extension
##
###############################################################################

file_get_extension () {
    local input="$1"
    
    local file="${input##*/}"
    
    local base="${file%.*}"
    local base2="${base%.*}"
    local ext="${file##*.}"
    local ext2="${base##*.}"
    local ext=$( tr "[A-Z]" "[a-z]" <<< "$ext")
    local ext2=$(tr "[A-Z]" "[a-z]" <<< "$ext2")

    if [[ "$ext2" == "tar" ]]
    then
        ext="${ext2}.${ext}"
        base="$base2"
    fi
    
    echo "$ext"
    
}

###############################################################################
## @brief function to get the dir of a file
##
## @param input     pathname to parse
##
## @return 0 on success
## @retval stdout the dir
##
###############################################################################

file_get_dir () {
    local input="$1"
    
    local dir="${input%/*}"
    if [[ "$dir" != "$input" ]]
    then
        echo "${dir}/"
    fi
    
}
###############################################################################
## @brief function to test for true
##
## @param value     the value to test
## @param default   the default return value if no match
##
## @return 0 for true, 1 for false
##
## @details
## case insensitive matching of true/ false / yes / no / 0 (false)/ 1 (true)
##
###############################################################################

istrue () {
    
   case "$1" in
        [nN][oO])
            false
            ;;
        [yY][eE][sS])
            true
            ;;
        [fF][aA][lL][sS][eE])
            false
            ;;
        [tT][rR][uU][eE])
            true
            ;;
        0)
            false
            ;;
        1)
            true
            ;;
        *)
            ##### if there is a second numeric arg return it by itself,#####
            ##### otherwise return the default of false #####
            
            if [ -n "$2" ]
            then
                return $2
            else
                false
            fi
            ;;
    esac
    
}

###############################################################################
## @brief function to proccess a file
## 
## @param myline     line from a ftp mirror file
##
## @details
## global vars
## @param indir                   dir the original file(s) will be placed in
## @param outdir                  dir to place the output in

## @param tmp                     the temp dir

##
## note this function echoes to fd 3 when finished and is called by mainloop
## multi proccesseing
##
###############################################################################

dofile () {
    local myline=$1

    local sourcedir=${indir//\/\///}
    local sourcedir=${sourcedir//\/\///}
    local tmpdir
    local dir=""
    
    tmpdir=$(mktemp -d -p "$tmp" "${dsname}XXXXXXXXXX") || {
        printerror "mktemp"
        echo >&3
        return
    }

    if ! grep -q -e "^get" <<< "$myline"
    then
        echo >&3
        rm -rf "${tmpdir}"
        return
    fi
    
    ##### make an array of files #####
            
    local i=0
    local files
    local line
    while read line
    do
        files[i++]=$(sed 's:.*/::' <<<"$line" | sed 's/.* -o //' | sed 's/%20/ /g')
    done < <( tr ";" "\n" <<<"$myline" )
    
    ##### get the last file name #####
    
    local file="${files[@]:(-1)}"
    
    if ! istrue "$ignoredir" && grep -q -e "$sourcedir/" <<<"$myline"
    then
        dir="$(sed "s|.*$sourcedir/\(.*\) [A-Za-z]*:/.*|\1|" <<<"$myline")/"
    fi
    
    
    local ext=$(file_get_extension "$file")
    local base=$(file_get_basename "$file")
    
    local ts=$(getdate <<< "$myline")
    local run=$(getrun <<< "$myline")
    local hour=$(gethour <<< "$myline")


    lftp -e "$(subtmplftp "${tmpdir}" <<<"$myline") ; exit" > /dev/null 2> /dev/null

    dofile_sub "$file" "$ext" "$tmpdir" "$ts" "$run" "$hour" ${files[@]}

    local status=$?

    if (($status == 0))
    then
        
        ##### mv the files to the source dir #####
        
        local f
        for f in "${files[@]}"
        do
            if [ -f "${tmpdir}/${f}" ]
            then
                mv "${tmpdir}/${f}" "${indir}/${dir}${f}"
            fi
        done
        
    fi
    
    rm -rf "${tmpdir}"
    echo >&3 "$myline"
    
    return $status
}

#### the following code came mostly from grib_contour and is gpl2

dofile_sub() {
    local file="$1"
    local ext="$2"
    local tmpdir="$3"
    local ts="$4"
    local run="$5"
    local hour="$6"
    local files=("${@:7}")
    
    local gribfile="${tmpdir}/$file"
    local msg
    local umsg
    local vmsg




    msg=$(getgribindex "$gribfile" "HGT=.* 100000-ISBL")
    plot "$gribfile" 1000hgt "$msg" 20 "$hour" 03 "$run" "$ts" 
    
    msg=$(getgribindex "$gribfile" "TMP=.* 100000-ISBL")
	plot "$gribfile" 1000t "$msg" 1 "$hour" 03 "$run" "$ts"
    
    umsg=$(getgribindex "$gribfile" "UGRD=.* 100000-ISBL")
    vmsg=$(getgribindex "$gribfile" "VGRD=.* 100000-ISBL")
	windplot "$gribfile" $gribfile 1000wind "$umsg" "$vmsg" 5 "$hour" 03 "$run" "$ts"



	msg=$(getgribindex "$gribfile" "HGT=.* 92500-ISBL")
    plot "$gribfile" 925hgt "$msg" 20 "$hour" 03 "$run" "$ts"
	
    msg=$(getgribindex "$gribfile" "TMP=.* 92500-ISBL")
	plot "$gribfile" 925t "$msg" 1 "$hour" 03 "$run" "$ts"
	
    umsg=$(getgribindex "$gribfile" "UGRD=.* 92500-ISBL")
    vmsg=$(getgribindex "$gribfile" "VGRD=.* 92500-ISBL")
	windplot "$gribfile" $gribfile 925wind "$umsg" "$vmsg" 5 "$hour" 03 "$run" "$ts"
		
	

    #msg=$(getgribindex "$gribfile" "HGT=.* 85000-ISBL")
    #plot "$gribfile" 850hgt "$msg" 20 "$hour" 03 "$run" "$ts"
	
    #msg=$(getgribindex "$gribfile" "TMP=.* 85000-ISBL")
	#plot "$gribfile" 850t "$msg" 1 "$hour" 03 "$run" "$ts"
	
    #umsg=$(getgribindex "$gribfile" "UGRD=.* 85000-ISBL")
    #vmsg=$(getgribindex "$gribfile" "VGRD=.* 85000-ISBL")
	#windplot "$gribfile" $gribfile 850wind "$umsg" "$vmsg" 5 "$hour" 03 "$run" "$ts"



	#msg=$(getgribindex "$gribfile" "HGT=.* 70000-ISBL")
    #plot "$gribfile" 700hgt "$msg" 20 "$hour" 03 "$run" "$ts"
	
    #msg=$(getgribindex "$gribfile" "TMP=.* 70000-ISBL")
	#plot "$gribfile" 700t "$msg" 1 "$hour" 03 "$run" "$ts"
	
    #umsg=$(getgribindex "$gribfile" "UGRD=.* 70000-ISBL")
    #vmsg=$(getgribindex "$gribfile" "VGRD=.* 70000-ISBL")
	#windplot "$gribfile" $gribfile 700wind "$umsg" "$vmsg" 5 "$hour" 03 "$run" "$ts"


	
	msg=$(getgribindex "$gribfile" "HGT=.* 50000-ISBL")
    plot "$gribfile" 500hgt "$msg" 20 "$hour" 03 "$run" "$ts"
	
    msg=$(getgribindex "$gribfile" "TMP=.* 50000-ISBL")
	plot "$gribfile" 500t "$msg" 1 "$hour" 03 "$run" "$ts"
	
    umsg=$(getgribindex "$gribfile" "UGRD=.* 50000-ISBL")
    vmsg=$(getgribindex "$gribfile" "VGRD=.* 50000-ISBL")
	windplot "$gribfile" $gribfile 500wind "$umsg" "$vmsg" 10 "$hour" 03 "$run" "$ts"



	msg=$(getgribindex "$gribfile" "HGT=.* 30000-ISBL")
    plot "$gribfile" 300hgt "$msg" 20 "$hour" 03 "$run" "$ts"
	
    msg=$(getgribindex "$gribfile" "TMP=.* 30000-ISBL")
	plot "$gribfile" 300t "$msg" 1 "$hour" 03 "$run" "$ts"
	
    umsg=$(getgribindex "$gribfile" "UGRD=.* 30000-ISBL")
    vmsg=$(getgribindex "$gribfile" "VGRD=.* 30000-ISBL")
	windplot "$gribfile" $gribfile 300wind "$umsg" "$vmsg" 10 "$hour" 03 "$run" "$ts"


	
	msg=$(getgribindex "$gribfile" "HGT=.* 20000-ISBL")
    plot "$gribfile" 200hgt "$msg" 20 "$hour" 03 "$run" "$ts"
	
    msg=$(getgribindex "$gribfile" "TMP=.* 20000-ISBL")
	plot "$gribfile" 200t "$msg" 1 "$hour" 03 "$run" "$ts"
	
    umsg=$(getgribindex "$gribfile" "UGRD=.* 20000-ISBL")
    vmsg=$(getgribindex "$gribfile" "VGRD=.* 20000-ISBL")
	windplot "$gribfile" $gribfile 200wind "$umsg" "$vmsg" 10 "$hour" 03 "$run" "$ts"

	
	msg=$(getgribindex "$gribfile" "PRMSL=.*  0-MSL")
	plot "$gribfile" pmsl "$msg" 200 "$hour" 03 "$run" "$ts"
}

###############################################################################
## @brief function to plot the data
##
## @param gribfile  full path to the grib file to plot
## @param name      name of the product ie: 925hgt
## @param gribmsg   the grib msg #
## @param interval  interval apart the contours are
## @param timee     the forcast hour in the run
## @param incr      how many hours apart the frames are
## @param extra     extra args to pass to grib_contour
##
## @details
## global vars
## @param wwwdisk   the base web dir to write to "/var/www/html/"
## @param run       the run of the model "00"
## @param dsname    name of the dataset
##
###############################################################################

plot () {
	local gribfile="$1"
	local name="$2"
	local grbmsg="$3"
	local interval="$4"
	local timee="$5"
	local incr="$6"
    local run="$7"
    local ts="$8"
	local extra="$9"
    
    local zip
    local kml
	zip="${outdir}/${dsname}/${name}${ts}${run}${timee}.kmz"
	kml="${name}${ts}${run}${timee}.kml"
	
	if [[ -f "$zip" ]]
	then
		rm "$zip"
	fi
	
	nice -n 10 grib_contour -g "${gribfile}" -m "$grbmsg" \
                            -i "$interval" -s "$name" \
                            -k "$kml" -z "$zip" \
                            "$extra" 

	
    appendkml "$name" "$timee" "$incr" "$grid" "$run" "$ts"

}


###############################################################################
## @brief function to plot the wind data
##
## @param ufile     full path to the u grib file to plot
## @param vfile     full path to the u grib file to plot
## @param name      name of the product ie: 925hgt
## @param umsg      the u grib msg #
## @param vmsg      the v grib msg #
## @param interval  interval apart the contours are
## @param timee     the forcast hour in the run
## @param incr      how many hours apart the frames are
## @param extra     extra args to pass to grib_contour
##
## @details
## global vars
## @param wwwdisk   the base web dir to write to "/var/www/html/"
## @param run       the run of the model "00"
## @param dsname    name of the dataset
##
###############################################################################

windplot () {
	local ufile="$1"
	local vfile="$2"
	local name="$3"
	local umsg="$4"
	local vmsg="$5"
	local interval="$6"
	local timee="$7"
	local incr="$8"
	local run="${9}"
    local ts="${10}"
    local extra="${11}"
    
    local zip
    local kml
	zip="${outdir}/${dsname}/${name}${ts}${run}${timee}.kmz"
	kml="${name}${ts}${run}${timee}.kml"
	
	if [[ -f "$zip" ]]
	then
		rm "$zip"
	fi
	
	nice -n 10 grib_contour -w -u "${ufile}" -v "${vfile}" \
													-U $umsg -V $vmsg \
													-i $interval -s $name \
													-k $kml -z "$zip" \
													$extra 
	
	appendkml "$name" "$timee" "$incr" "$grid" "$run" "$ts"

	#appendgeoext $name $timee $incr $grid
	#appendmapfile "$name" "$zip"

}

getgribindex() {
    degrib -in "$1" -I |\
     grep "$2" |\
     cut -d "," -f 1 |\
     head -n 1 
}

###############################################################################
## @brief function to create the root kml file
##
## @param name  the name of the product ie: 925hgt
##
## @details
## global vars
## @param wwwdisk   the base web dir to write to "/var/www/html/"
## @param run       the run of the model "00"
## @param www       the base url for the website
## @param dsname    name of the dataset
##
###############################################################################

mkrootkml () {
	local name="$1"
	
	local frames="${outdir}/${dsname}/${name}.kml"
	
	cat > $frames << EOF
<?xml version="1.0" encoding="UTF-8"?>
<kml xmlns="http://earth.google.com/kml/2.2">
<Folder>
  <ScreenOverlay>
    <name>Key</name>
    <visibility>1</visibility>
		<Icon>
      <href>${www}/kml/images/${name}.png</href>
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


}



###############################################################################
## @brief function to append the new frame to the root kml
##
## @param name  the name of the product ie: 925hgt
## @param hr    the forcast hour in the run
## @param incr  how many hours apart the frames are
## @param grid  optional name to prefix onto the kml name
##
## @details
## global vars
## @param wwwdisk   the base web dir to write to "/var/www/html/"			
## @param run       the run of the model "00"
## @param www       the base url for the website
## @param dsname    name of the dataset
##
###############################################################################

appendkml () {
	local name="$1"
	local hr="$2"
	local incr="$3"
	local grid="$4"
	local run="$5"
	local ts="$6"
	
	local frames="${outdir}/${dsname}/${name}.kml"

	if ! [ -f "$frames" ]
	then
        mkrootkml "${name}"
    fi
    
    ##### lock the file #####
	
	local lock="$tmp/grib_contour_hfdkjshfakldf${dsname}.${name}.kml.lock"

	while ! mkdir "$lock" > /dev/null
	do
		sleep 1
	done
	
    ##### test if the kml is older than 6 hours #####
    
	#local frametime;
    #local nowtime;
    
	#frametime=$(stat --printf "%Y\n" "$frames")
    #nowtime=$(date "+%s")
    
    #if (( frametime + 21600 < nowtime))
    #then
    #    mkrootkml "${name}"
    #fi
    
    local zip
	if [[ "$grid" != "" ]]
	then
		zip="${grid}.${name}${ts}${run}${timee}.kmz"
	else
		zip="${name}${ts}${run}${timee}.kmz"
	fi


	
	begin=$(date -d "$ts $run GMT $hr hours" "+%FT%TZ" -u)
	end=$(date -d "$ts $run GMT $hr hours $incr hours" "+%FT%TZ" -u)

ed -s $frames << EOF
$ -2
a
  <NetworkLink>
    <name> ${ts}${run}Z + ${hr} ${grid}.${name}</name>
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
.
w
EOF

	##### remove the lock #####
	
	rmdir "$lock"

}

main

