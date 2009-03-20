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

outfile="${name}.php"


cat > "$outfile" <<EOF
<div class=data>
  <h2>${fullname}</h2>
  <p>
    ${description}
  </p>
  
  <h3>kml with all datasets and run times</h3>
  <h4><a href="kml/${name}.kml">${name}.kml</a></h4>
  <h3>kml with all datasets and the latest time</h3>
  <h4><a href="kml/${name}-latest.kml">${name}-latest.kml</a></h4>
EOF

echo "$levels" | while read lev_n lev_fn
do
  echo "$products" | while read prod_n prod_fn
  do

cat >> "$outfile" <<EOF
  <div>
    <h4>${lev_fn} ${prod_fn}</a></h4>
    <a href="kml/screenshot/${name}_${lev_n}${prod_n}.jpg">
      <img src="kml/screenshot/${name}_${lev_n}${prod_n}.png" alt=screenshot>
    </a>
  </div>
EOF
  
  done
done
echo "</div>" >> "$outfile"


