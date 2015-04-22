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

name=nam_firewx_hires
fullname="5 km Resolution Western CONUS NAM Forecast Model"

baseurl="ftp://ftp.ncep.noaa.gov/pub/data/nccf/com/nam/prod/nam.%date8%/"

pattern="nam.t%run2%z.firewxnest.hiresf%hour2%.tm00.grib2"

description='Data from <a href=\"http://www.ncep.noaa.gov/\">
National Centers for Environmental Prediction</a> 
generated once daily is contoured and converted to kml
for forecast hours 0-36 in 1 hour increments, and 36-60 in 3 hour increments.
<h3>NOTE: This product may be preempted by the National Hurricane Center</h3>'

levels="200 200 mb
300 300 mb
500 500 mb
700 700 mb
850 850 mb
925 925 mb
1000 1000 mb"

products200="wind Wind
t Temperature
rh Relative Humidity
hgt Heights"

products300="wind Wind
t Temperature
rh Relative Humidity
hgt Heights"

products500="wind Wind
t Temperature
rh Relative Humidity
hgt Heights
thk Thickness"

products700="wind Wind
t Temperature
rh Relative Humidity
hgt Heights
thk Thickness"

products850="wind Wind
t Temperature
rh Relative Humidity
hgt Heights
thk Thickness"

products925="wind Wind
t Temperature
rh Relative Humidity
hgt Heights
thk Thickness"

products1000="wind Wind
t Temperature
rh Relative Humidity
hgt Heights"

levels2="0 0 - none"

products2="pwat Perceptible Water
pmsl Mean Sea Level Pressure
cape Convective Available Potential Energy"


times="latest Latest
00 00Z
06 06Z
12 12Z
18 18Z"

runs="latest Latest
00 00Z
06 06Z
12 12Z
18 18Z"

hours="36 1
60 3"

prodmap="   plot,       HGT,        hgt,    20,     36 1|60 3,  -H,
            diffplot,   HGT,        thk,    20,     36 1|60 3,    , HGHT
            plot,       TMP,        t,      1,      36 1|60 3,    ,
            plot,       RH,         rh,     10,     36 1|60 3,    ,
            windplot,   UGRD,       wind,   5,      36 1|60 3,    , VGRD
            plot,       CAPE,       cape,   200,    36 1|60 3,    ,
            plot,       PWAT,       pwat,   4,      36 1|60 3,  -I,
            plot,       PRMSL,      pmsl,   200,    36 1|60 3, -H,"


