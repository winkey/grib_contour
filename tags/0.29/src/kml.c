/***************************************************************************
 *  kml.c
 *
 *  Thursday May 15 21:46:00 2008
 *  Copyright  2008  winkey
 *  <rush@winkey.org>
 ****************************************************************************/
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor Boston, MA 02110-1301,  USA
 */

#include <stdio.h>

#include "buffer.h"


void kml_header (
	buffer *buf)
{
	
	buffer_printf(buf, "<?xml version=\"1.0\" encoding=\"utf-8\" ?>\n");
	buffer_printf(buf, "<kml xmlns=\"http://www.opengis.net/kml/2.2\">\n");
	buffer_printf(buf, "<Document>\n");

 return;
}

void kml_footer (
	buffer *buf)
{
	
	buffer_printf(buf, "</Document>\n");
	buffer_printf(buf, "</kml>\n");
	
	return;
}

void kml_placemark_header (
	buffer *buf,
	char *name,
	char *desc,
	char *styleid)
{
	
	buffer_printf(buf, "  <Placemark>\n");
	if (name)
		buffer_printf(buf, "    <name>%s</name>\n", name);
	if (desc) {
		buffer_printf(buf, "    <description>");
		buffer_printf(buf, "%s", desc);
		buffer_printf(buf, "    </description>\n");
	}
	buffer_printf(buf, "    <styleUrl>#%s</styleUrl>\n", styleid);
	return;
}
	
void kml_linestring_header (
	buffer *buf,
	int extrude,
	int tessellate)
{

	buffer_printf(buf, "    <LineString>\n");
	if (extrude)
		buffer_printf(buf, "      <extrude>1</extrude>\n");
	if (tessellate)		
		buffer_printf(buf, "      <tessellate>1</tessellate>\n");
	buffer_printf(buf, "      <coordinates>");

	return;
}

void kml_linestring_footer (
	buffer *buf)
{

	
	buffer_printf(buf, "</coordinates>\n");
	buffer_printf(buf, "    </LineString>\n");

	return;
}

void kml_linestyle (
	buffer *buf,
	char *id,
	char *rgb,
	char *alpha,
	int width)
{

	buffer_printf(buf, "    <Style id=\"%s\">\n", id);
	buffer_printf(buf, "  	  <LineStyle>\n");
	buffer_printf(buf, "        <color>%s%c%c%c%c%c%c</color>\n", alpha,
								rgb[4], rgb[5], rgb[2], rgb[3], rgb[0], rgb[1]);
	buffer_printf(buf, "        <width>%i</width>\n", width);
	buffer_printf(buf, "      </LineStyle>\n");
	buffer_printf(buf, "    </Style>\n");
	
	return;
}

void kml_placemark_footer (
	buffer *buf)
{

  buffer_printf(buf, "  </Placemark>\n");
	
	return;
}


