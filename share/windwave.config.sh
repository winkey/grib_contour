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

name=windwave
fullname="0.5 deg Wind Wave"

description='Data from <a href=\"http://www.ncep.noaa.gov/\">
National Centers for Environmental Prediction</a> 
generated four times daily is contoured and converted to kml
for forecast hours 0-180 in 3 to 6 hour increments.'

products="hghtww Significant height of wind waves
perdww Mean period of wind waves
htsgw Significant height of combination wind waves and swell"

times="00 00Z
06 06Z
12 12Z
18 18Z"

runs="latest Latest
00 00Z
06 06Z
12 12Z
18 18Z"

screenshots=$(
  echo "$products" | while read prod_n prod_fn
  do
    echo ${name}_${prod_n}.jpg
  done
)

thumbs=$(
  echo "$products" | while read prod_n prod_fn
  do
    echo ${name}_${prod_n}.png
  done
)
