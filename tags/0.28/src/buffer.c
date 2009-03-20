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
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "buffer.h"
#include "error.h"

/*******************************************************************************
	function to allocate memory for a buffer
*******************************************************************************/

void buffer_alloc (
	buffer *buf,
	size_t need)
{
	char *temp;
	
	/***** if no memory alocate *****/

	if (!buf->alloced) {
		buf->alloced = need;
		if (!(buf->buf = malloc (buf->alloced)))
			ERROR("buffer_alloc");
		
		buf->buf[0] = 0;
	}

	/***** if not enough memory realocate *****/

	else {
		while (buf->alloced < buf->used + need) {

			buf->alloced *= 2;
			if (!(temp = realloc (buf->buf, buf->alloced)))
				ERROR("buffer_alloc");
			
			buf->buf = temp;
		}
	}
	
	return;
}

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
	char *format,
	...)
{

	va_list ap;
	int result = 0;
	int need = 0;

	va_start (ap, format);
	need = 1 + vsnprintf (NULL, 0, format, ap);
	if (buf->alloced < buf->used + need)
		buffer_alloc(buf, need);
	va_end (ap);
	
	va_start (ap, format);
	result = vsprintf (buf->buf + buf->used, format, ap);
	buf->used += result;
	va_end (ap);

	return result;
}

/*******************************************************************************
	function to free a buffer

	args:
						buf			the buffer to free
	
 returns:
						nothing
*******************************************************************************/

void buffer_free(
	buffer *buf)
{
	
	free(buf->buf);
	
	return;
}
