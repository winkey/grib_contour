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


scale=$1
lable=$2
output=$3

count=0
last=0
x=5
cwidth=20
len=0;

##### count colors  and get max text width #####

while read value color
do
	count=$((count + 1))
	if [ `echo -n $value | wc -c` -gt "$len"  ]
	then
		len=`echo -n $value | wc -c`
	fi
		
done < $scale

##### figure out width of image #####

width=$((count*$cwidth+15))

if [ "$width" -gt "720" ]
then
	cwidth=$((720/$count))
	width=$((count*$cwidth+15))
fi

##### get label start pos #####

lablen=`echo -n $lable | wc -c`
stx=$(($width - 7 - 4 * $lablen))




args=(-size ${width}x36 xc:white )

while read value color
do
	xx=$(($x+$cwidth))
	
	##### draw color #####
	
	args=("${args[@]}" -fill "#$color" -stroke black -draw "rectangle $x,5 $xx,18")
	
	##### draw value #####
	mylen=`echo -n $value | wc -c`
	if [ "$(($xx-4-$len*4))" -gt "$last" ] && [ "$(($xx+4+$len*4))" -lt "$stx" ]
	then
		tx=$(($xx-4*$mylen))
		args=("${args[@]}" -pointsize 14 -fill black -draw "text ${tx},34 '${value}'")
		last=$(($xx+4*$len))
	fi
	
	x=$xx
done < $scale

##### draw label #####

args=("${args[@]}" -pointsize 12 -fill black -draw "text ${stx},33 '${lable}'")


##### build the image #####

convert "${args[@]}" $output

