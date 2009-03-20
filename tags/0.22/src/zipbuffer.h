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
 
#ifndef _ZIPBUFFER_H
#define _ZIPBUFFER_H

/*******************************************************************************
	function to open the zip file
	
	args:
						name			the filename of the zip archive

	returns:
						pointer to the zip structure
						exit()s on error
*******************************************************************************/

struct zip *zipbuffer_open (
	char *name);

/*******************************************************************************
	function to add the buffer to the zip file
	
	args:
						name			the filename of the file to add to the zip archive
						zip				pointer to the zip structure
						buf				the buffer to add

	returns:
						nothing
*******************************************************************************/

void zipbuffer_add (
	char *name,
	struct zip *za,
	buffer *buf);


/*******************************************************************************
	function to close the zip file

	args:
						zip				pointer to the zip structure

	returns:
						nothing
*******************************************************************************/

void zipbuffer_close (
	struct zip *za);


#endif /* _ZIPBUFFER_H */

