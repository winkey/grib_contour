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
source /usr/local/bin/generic2.sh

export PATH="$PATH:/usr/local/bin

run="00"

serv="ftp://ftpprd.ncep.noaa.gov/pub/data/nccf/com/gfs/prod/"
servb="http://www.ftp.ncep.noaa.gov/data/nccf/com/gfs/prod/"
wwwdisk="/home/rush/public_html/weather/kml/sst"
www="http://atmos.ucsd.edu//kml/sst"

gribfile="rtgssthr_grb_0.083_awips.grib2"


if [[ ! -d "${wwwdisk}/" ]]
then
	mkdir -p "${wwwdisk}/"
fi

if ! getgrib "${servb}/sst.${datee}" "$gribfile"
then
	exit
fi

mkrootkml "${level}sst"

plot "${tmp}/${gribfile}" "sst" 1 .75 0 24

rm "${tmp}/${gribfile}"


