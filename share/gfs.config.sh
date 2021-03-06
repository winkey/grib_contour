#!bin/bash
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

name=gfs
fullname=".5 Degree Resolution GFS Forecast Model"

description='Data from <a href=\"http://www.ncep.noaa.gov/\">
National Centers for Environmental Prediction</a> 
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

products2="pwat Perceptible Water
pmsl Mean Sea Level Pressure
pcp 6 Hour Total Precipitation
rain 6 Hour Total Rain Precipitation
snow 6 Hour Total Snow Precipitation
frez 6 Hour Total Freezing Precipitation
pellet 6 Hour Total Pellet Precipitation
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



##### GFS MAPPING #####

#plottype            feed_name   our_name  interval time_valid    extra_args dependancys
prodmap="   plot,       HGHT,       hgt,    20,     237 03|384 12,  -H, 
            diffplot,   HGHT,       thk,    20,     237 03|384 12,    , HGHT
            plot,       TMPK,       t,      1,      237 03|384 12,    ,
            plot,       RELH,       rh,     10,     237 03|384 12,    ,
            windplot,   UREL;VREL,  wind,   5,      237 03|384 12,    ,
            plot,       CAPE,       cape,   200,    237 03|384 12,    ,
            plot,       PWTR,       pwat,   4,      237 03|384 12,  -I,
            plot,       P06M,       pcp,    4,      240 06,         -I,
            andplot,    WXTS06,     snow,   4,      240 06,         -I, P06M
            andplot,    WXTZ06,     frez,   4,      240 06,         -I, P06M
            andplot,    WXTR06,     rain,   4,      240 06,         -I, P06M
            andplot,    WXTP06,     pellet, 4,      240 06,         -I, P06M
            plot,       PMSL,       pmsl,   200,    237 03|384 12,  -H,"


