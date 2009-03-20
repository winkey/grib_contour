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

name=nam_east
fullname="5 km Resolution Eastern CONUS NAM Forecast Model"

description='Data from <a href=\"http://www.ncep.noaa.gov/\">
National Centers for Environmental Prediction</a> 
generated twice daily is contoured and converted to kml
for forecast hours 0-48 in 1 hour increments.
<h3>NOTE: This product may be preempted by the National Hurricane Center</h3>'

levels="300 300 mb
500 500 mb
700 700 mb
850 850 mb
925 925 mb"

products="t Temperature
rh Relative Humidity
hgt Heights"

levels2="0 0 - none"

products2="pwat Perceptible Water
pmsl Mean Sea Level Pressure
cape Convective Available Potential Energy
pcp 1 Hour Total Precipitation
rain 1 Hour Total Rain Precipitation
snow 1 Hour Total Snow Precipitation
frez 1 Hour Total Freezing Precipitation
pellet 1 Hour Total Pellet Precipitation"

times="00 00Z
12 12Z"

screenshots=$(
  echo "$levels" | while read lev_n lev_fn
  do
    echo "$products" | while read prod_n prod_fn
    do
      echo ${name}_${lev_n}${prod_n}.jpg
    done
  done
  echo "$levels2" | while read lev_n lev_fn
  do
    echo "$products2" | while read prod_n prod_fn
    do
      echo ${name}_${prod_n}.jpg
    done
  done
)

thumbs=$(
  echo "$levels" | while read lev_n lev_fn
  do
    echo "$products" | while read prod_n prod_fn
    do
      echo ${name}_${lev_n}${prod_n}.png
    done
  done
  echo "$levels2" | while read lev_n lev_fn
  do
    echo "$products2" | while read prod_n prod_fn
    do
      echo ${name}_${prod_n}.png
    done
  done
)
