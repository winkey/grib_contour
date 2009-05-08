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

outfile="../kml/${name}-latest.kml"

##### header #####

cat > "$outfile" <<EOF
<?xml version="1.0" encoding="UTF-8"?>
<kml xmlns="http://earth.google.com/kml/2.2">
<Document>
  <name>${fullname}</name>
  <description><![CDATA[
    ${description}
  ]]></description>
EOF

##### levels #####

echo "$levels" | while read lev_n lev_fn
do

cat >> "$outfile" <<EOF
  <Folder>
    <name>${lev_fn}</name>
    <visibility>0</visibility>
EOF
  
  ##### products #####

	ref="products$lev_n"
  echo "${!ref}" | while read prod_n prod_fn
  do

cat >> "$outfile" <<EOF
    <Folder>
      <name>${lev_fn} ${prod_fn}</name>
      <visibility>0</visibility>
      <Style>
        <ListStyle>
          <listItemType>radioFolder</listItemType>
          <bgColor>00ffffff</bgColor>
        </ListStyle>
      </Style>
      <Folder>
        <name>off</name>
        <visibility>0</visibility>
      </Folder>
EOF
    
    ##### times #####

cat >> "$outfile" <<EOF
      <NetworkLink>
        <name>Latest</name>
        <visibility>0</visibility>
        <open>0</open>
        <Link>
          <href>/home/rush/public_html/weather/kml/${name}/latest/${lev_n}${prod_n}.kml</href>
        </Link>
      </NetworkLink>
EOF
 
echo "    </Folder>" >> "$outfile"

  done

echo "  </Folder>" >> "$outfile"

done

##### levels 2 #####

echo "$levels2" | while read lev_n lev_fn
do

cat >> "$outfile" <<EOF
  <Folder>
    <name>${lev_fn}</name>
    <visibility>0</visibility>
EOF
  
  ##### products 2 #####

  echo "$products2" | while read prod_n prod_fn
  do

cat >> "$outfile" <<EOF
    <Folder>
      <name>${prod_fn}</name>
      <visibility>0</visibility>
      <Style>
        <ListStyle>
          <listItemType>radioFolder</listItemType>
          <bgColor>00ffffff</bgColor>
        </ListStyle>
      </Style>
      <Folder>
        <name>off</name>
        <visibility>0</visibility>
      </Folder>
EOF
    
    ##### times 2 #####

cat >> "$outfile" <<EOF
      <NetworkLink>
        <name>Latest</name>
        <visibility>0</visibility>
        <open>0</open>
        <Link>
          <href>/home/rush/public_html/weather/kml/${name}/latest/${prod_n}.kml</href>
        </Link>
      </NetworkLink>
EOF
  
echo "    </Folder>" >> "$outfile"

  done

echo "  </Folder>" >> "$outfile"

done

cat >> "$outfile" <<EOF
</Document>
</kml>
EOF