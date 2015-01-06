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

name=coamps_cencoos
fullname=".2 Deg Resolution Central and Northern California COAMPS Forecast Model"

description='Data from <a href=\"https://www.fnmoc.navy.mil/public/\">
Fleet Numerical Meteorology and Oceanography Center</a> 
generated twice daily is contoured and converted to kml
for forecast hours 0-48 in 3 hour increments.'

levels="500 500 mb
700 700 mb
850 850 mb
925 925 mb
1000 1000 mb"

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

#coamps_cencoos
prodmap="   plot,       geop_ht,    hgt,    20,     06, -h,
            diffplot,   geop_ht,    thk,    20,     06, ,   geop_ht
            plot,       air_temp,   t,      1,      06, ,
            plot,       rltv_hum,   rh,     10,     06, ,
            windplot,   wnd_ucmp,   wind,   5,      06, ,   wnd_vcmp
            plot,       ttl_prcp,   pcp,    4,      06, -I,
            plot,       pres,       pmsl,   200,    06, -h,"


