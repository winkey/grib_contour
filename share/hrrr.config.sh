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

name=hrrr
fullname="2.5km Resolution CONUS High-Resolution Rapid Refresh Forecast Model"

description='Data from <a href=\"http://www.ncep.noaa.gov/\">
National Centers for Environmental Prediction</a> 
generated four times daily is contoured and converted to kml
for forecast hours 0-15 in 1 hour increments.'

levels="500 500 mb
700 700 mb
850 850 mb
1000 1000 mb"

products500="wind Wind
t Temperature
hgt Heights
thk Thickness"

products700="wind Wind
t Temperature
hgt Heights
thk Thickness"

products850="wind Wind
t Temperature
hgt Heights
thk Thickness"

products925="wind Wind
t Temperature
thk Thickness"

products1000="wind Wind
t Temperature
hgt Heights"

levels2="0 0 - none"

products2="pwat Perceptible Water
pmsl Mean Sea Level Pressure
pcp 1 Hour Total Precipitation
cape Convective Available Potential Energy
refd1000 Reflectivity at 1 km above ground level
maxrefd1000 Maximum reflectivity at 1 km above ground level"

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


##### HRRR MAPPING #####

prodmap="   plot,       HGHT,       hgt,    20,     15 1,   -h,
            diffplot,   HGHT,       thk,    20,     15 1,     ,   HGHT
            plot,       TMPK,       t,      1,      15 1,     ,
            plot,       RELH,       rh,     10,     15 1,     ,
            windplot,   UREL,       wind,   5,      15 1,     ,   VREL
            plot,       CAPE,       cape,   200,    15 1,     ,
            plot,       PWTR,       pwat,   4,      15 1,   -I,
            plot,       P01M,       pcp,    4,      15 1,   -I,
            plot,       PMSL,       pmsl,   200,    15 1,   -h,
            plot,       REFD        refd1000,   5,      15 1,     ,
            plot,       MAXREF1000  maxrefd1000,   5,  15 1, ,"


  
