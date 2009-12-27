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

name=ocean
fullname=".25 Degree Resolution Global Ocean Model"

description='Data from <a href=\"https://www.fnmoc.navy.mil/public/\">
Fleet Numerical Meteorology and Oceanography Center</a> 
generated once daily is contoured and converted to kml'

products="sst Sea Surface Temperature
ice Sea Ice Coverage"

times="12 12Z"

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
