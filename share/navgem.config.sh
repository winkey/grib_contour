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

name=navgem
fullname="1 Deg Resolution Navy Global Environmental Model"

description='Data from <a href=\"https://www.fnmoc.navy.mil/public/\">
Fleet Numerical Meteorology and Oceanography Center</a> 
generated four times daily is contoured and converted to kml
for forecast hours 0-180 in 3 hour increments.'

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

products2="pmsl Mean Sea Level Pressure
pcp 3 Hour Total Precipitation"

times="latest Latest
00 00Z
12 12Z"

runs="latest Latest
00 00Z
12 12Z"


#navgem
prodmap="   plot,       geop_ht,    hgt,    20,     144 06,  -H,
            diffplot,   geop_ht,    thk,    20,     144 06,    , geop_ht
            plot,       air_temp,   t,      1,      144 06,    ,
            plot,       rltv_hum,   rh,     10,     144 06,    ,
            windplot,   wnd_ucmp,   wind,   5,      144 06,    , wnd_vcmp
            plot,       ttl_prcp,   pcp,    4,      144 06,  -I,
            plot,       pres,       pmsl,   200,    144 06,  -H,"

