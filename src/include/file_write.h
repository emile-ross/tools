#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

size_t ssnprintf(char *buffer, size_t buffer_size, const char *format, ...)
{
	va_list ap;
	size_t return_value;
	
	va_start(ap, format);
	return_value = (size_t)vsnprintf(buffer, buffer_size, format, ap);
	if (buffer_size != 0 && return_value > buffer_size)
	{
		fprintf(stderr, "Truncated write, writing %zu bytes to a buffer of size %zu", return_value, buffer_size);
		if (buffer != NULL)
		{
			free(buffer);
		}
		exit(1);
	}
	va_end(ap);
	return return_value;
}
