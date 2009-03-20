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

source /usr/local/bin/generic2.sh

wwwdisk="/home/rush/public_html/weather/kml/ww"
www="http://winkey.org/weather/kml/ww"

path="$1"
run="$3"
hour="$4"
prod="$5"

tmp="/tmp"

if [[ "$hour" == "" ]]
then
	hour="00"
fi

if [[ ! -d "${wwwdisk}/${run}" ]]
then
	mkdir -p "${wwwdisk}/${run}"
fi

##### plot Significant hght of wind waves #####

if [[ "$prod" == "HGHTWW" ]]
then
	if [[ "$hour" == "00" ]]
	then
		mkrootkml "hghtww"
		if [[ ! -h "${wwwdisk}/latest" ]]
		then
			rm -f "${wwwdisk}/latest"
		fi
		ln -s "${wwwdisk}/${run}" "${wwwdisk}/latest"fi
	
	plot "$path" "hghtww" 1 20 $hour 03
	rm "$path"
fi

##### Mean period of wind waves #####

if [[ "$prod" == "PERDWW" ]]
then
	if [[ "$hour" == "00" ]]
	then
		mkrootkml "perdww"
	fi
	
	plot "$path" "perdww" 1 1 $hour 03
	rm "$path"
fi

##### Sig hght of comb wind waves/swell #####

if [[ "$prod" == "HTSGW" ]]
then
	if [[ "$hour" == "00" ]]
	then
		mkrootkml "htsgw"
	fi
	
	plot "$path" "htsgw" 1 5 $hour 03
	rm "$path"
fi

##### plot wind #####

if [[ "$prod" == "UREL" ]]
then
	vpath=$(echo "$path" | sed s/UREL/VREL/)
	
	if [[ -f "$vpath" ]]
	then
		if [[ "$hour" == "00" ]]
		then
			mkrootkml "${level}wind"
		fi
		
		windplot "$path" "$vpath" "${level}wind" 1.0 1.0 10 $hour 03

		rm "$path"
		rm "$vpath"
	fi
fi

if [[ "$prod" == "VREL" ]]
then
	upath=$(echo "$path" | sed s/VREL/UREL/)
	
	if [[ -f "$upath" ]]
	then
		if [[ "$hour" == "00" ]]
		then
			mkrootkml "wind"
		fi
		
		windplot "$upath" "$path" "wind" 1.0 1.0 10 $hour 03
		
		rm "$path"
		rm "$upath"
	fi
fi

