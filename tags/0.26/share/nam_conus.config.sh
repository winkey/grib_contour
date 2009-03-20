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

name=nam_conus
fullname="12km Resolution CONUS NAM Forecast Model"

description='Data from <a href=\"http://www.ncep.noaa.gov/\">
National Centers for Environmental Prediction</a> 
generated four times daily is contoured and converted to kml
for forecast hours 0-96 in 3 hour increments.'

levels="300 300 mb
500 500 mb
700 700 mb
850 850 mb
925 925 mb"

products="wind Wind
t Temperature
rh Relative Humidity
hgt Heights"

levels2="0 0 - none"

products2="pwat Perceptible Water
pmsl Mean Sea Level Pressure
pcp 3 Hour Total Precipitation
rain 3 Hour Total Rain Precipitation
snow 3 Hour Total Snow Precipitation
frez 3 Hour Total Freezing Precipitation
pellet 3 Hour Total Pellet Precipitation
pop Probability of Precipitation
popz Probability of Frozen Precipitation
popf Probability of Freezing Precipitation
tstm Probability of Thunderstorm
cape Convective Available Potential Energy"

times="00 00Z
06 06Z
12 12Z
18 18Z"

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

  
