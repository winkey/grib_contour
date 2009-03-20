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

name=ukmet
fullname="2.5 Degree Resolution UKMET Forecast Model"

description='Data from <a href=\"http://www.metoffice.gov.uk/\">
Met Office</a> 
generated four times daily is contoured and converted to kml
for forecast hours 0-72 in 6 to 12 hour increments.'

levels="200 200 mb
300 300 mb
500 500 mb
700 700 mb
850 850 mb
1000 1000 mb"

products200="wind Wind
t Temperature
hgt Heights"

products300="wind Wind
t Temperature
hgt Heights"

products500="wind Wind
t Temperature
rh Relative Humidity
hgt Heights"

products700="wind Wind
t Temperature
rh Relative Humidity
hgt Heights"

products850="wind Wind
t Temperature
rh Relative Humidity
hgt Heights"

products1000="hgt Heights"

products2="pmsl Mean Sea Level Pressure"

times="00 00Z
12 12Z"

screenshots=$(
  echo "$levels" | while read lev_n lev_fn
  do
		ref="products$lev_n"
    echo "${!ref}" | while read prod_n prod_fn
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
		ref="products$lev_n"
    echo "${!ref}" | while read prod_n prod_fn
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
