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

name=rap
fullname="20 km Resolution CONUS NCEP Rapid Refresh (RAP)  Forecast Model"

description='Data from <a href=\"http://www.ncep.noaa.gov/\">
National Centers for Environmental Prediction</a> 
generated twenty four times daily is contoured and converted to kml
for forecast hours 0-9 in 1 hour increments.'

levels="300 300 mb
500 500 mb
700 700 mb
850 850 mb
925 925 mb"

products300="wind Wind
t Temperature
rh Relative Humidity
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

products925="wind Wind
t Temperature
rh Relative Humidity
hgt Heights"


levels2="0 0 - none"

products2="pwat Perceptible Water
pmsl Mean Sea Level Pressure
cape Convective Available Potential Energy
refc Composite Reflectivity
refd1000 Reflectivity at 1 km above ground level
refd4000 Reflectivity at 4 km above ground level"


times="latest Latest
00 00Z
01 01Z
02 02Z
03 03Z
04 04Z
05 05Z
06 06Z
07 07Z
08 08Z
09 09Z
10 10Z
11 11Z
12 12Z
13 13Z
14 14Z
15 15Z
16 16Z
17 17Z
18 18Z
19 19Z
20 20Z
21 21Z
22 22Z
23 23Z"

runs="latest Latest
00 00Z
01 01Z
02 02Z
03 03Z
04 04Z
05 05Z
06 06Z
07 07Z
08 08Z
09 09Z
10 10Z
11 11Z
12 12Z
13 13Z
14 14Z
15 15Z
16 16Z
17 17Z
18 18Z
19 19Z
20 20Z
21 21Z
22 22Z
23 23Z"


