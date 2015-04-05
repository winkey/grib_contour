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

name=nam_conus_hires
fullname="5 km Resolution Eastern CONUS NAM Forecast Model"

description='Data from <a href=\"http://www.ncep.noaa.gov/\">
National Centers for Environmental Prediction</a> 
generated twice daily is contoured and converted to kml
for forecast hours 0-48 in 1 hour increments.
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
cape Convective Available Potential Energy
pcp 1 Hour Total Precipitation
rain 1 Hour Total Rain Precipitation
snow 1 Hour Total Snow Precipitation
frez 1 Hour Total Freezing Precipitation
pellet 1 Hour Total Pellet Precipitation"

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

prodmap="   plot,       HGHT,       hgt,    20,     03, -H,
            diffplot,   HGHT,       thk,    20,     03, ,   HGHT
            plot,       TMPK,       t,      1,      03, ,
            plot,       RELH,       rh,     10,     03, ,
            windplot,   UREL,       wind,   5,      03, ,   VREL
            plot,       CAPE,       cape,   200,    03, ,
            plot,       PWTR,       pwat,   4,      03, -I,
            plot,       P03M,       pcp,    4,      03, -I,
            andplot,    WXTS,       snow,   4,      03, -I, P03M
            andplot,    WXTZ,       frez,   4,      03, -I, P03M
            andplot,    WXTR,       rain,   4,      03, -I, P03M
            andplot,    WXTP,       pellet, 4,      03, -I, P03M
            plot,       PMSL,       pmsl,   200,    03, -H,
            plot,       POPF03,     popf,   10,     03, ,
            plot,       TSTM03,     tstm,   10,     03, ,
            plot,       POP03,      pop,    10,     03, ,
            plot,       POPZ03,     popz,   10,     03, ,"



