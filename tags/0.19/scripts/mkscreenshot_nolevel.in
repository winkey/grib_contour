#!/bin/bash
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

source $1

wd=$(pwd)

function shot {
  url="$1"
  fn="$2"

  ##### run ge #####

  googleearth "$url"&
  while ! xdotool search --onlyvisible --title "Google Earth"
  do
    sleep 1
  done
	
  sleep 20
	
  ##### save screenshot #####
	
  xdotool key "ctrl+alt+s"
  
  while ! xdotool search --onlyvisible --title --name "Save As"
  do
    sleep 1
  done

  while ! [[ "$fn" = "" ]]
  do
    key=${fn:0:1}
    if [[ "$key" = [[:upper:]] ]] ; then key="shift+$key" ; fi
    if [[ "$key" = "/" ]] ; then key="slash" ; fi
    if [[ "$key" = "." ]] ; then key="period" ; fi
    if [[ "$key" = "_" ]] ; then key="shift+underscore" ; fi
    xdotool key "$key"
    fn=${fn:1}
  done

  xdotool key "Return"

  ##### quit ge #####

  sleep 3
  xdotool key "alt+F4"
  sleep 3
  xdotool key "Tab"
  xdotool key "Return"
	
  while xdotool search --onlyvisible --title "Google Earth"
  do
    sleep 1
  done
}

echo "$products" | while read prod_n prod_fn
do
    
  fn="${wd}/${name}_${prod_n}.jpg"
  url="http://atmos.ucsd.edu/kml/${name}/latest/${prod_n}.kml"
    
  if [[ -f "$fn" ]]
  then
    echo remove
    rm "$fn"
  fi
    
  shot "$url" "$fn" > /dev/null

done

