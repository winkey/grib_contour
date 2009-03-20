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
 
#ifndef _BUFFER_H
#define _BUFFER_H

/*******************************************************************************
	buffer structure
	
	members:
							buf				the buffer
							alloced		amount of space allocated in the buffer
							used			amount of space used in the buffer
*******************************************************************************/

typedef struct {
	char *buf;
	size_t alloced;
	size_t used;
} buffer;

/*******************************************************************************
	function to print to a buffer

	args:
						buf			the buffer to print to
						fmt			the format string
						...			aditianal args that match the format string
	
 returns:
						the number of chars printed to the buffer, not includeing the \0
*******************************************************************************/

int buffer_printf(
	buffer *buf,
	char *fmt,
	...);

/*******************************************************************************
	function to free a buffer

	args:
						buf			the buffer to free
	
 returns:
						nothing
*******************************************************************************/

void buffer_free(
	buffer *buf);


#endif /* _BUFFER_H */

