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

char *bmalloc(const char *format, ...)
{
	va_list args, copy;
	va_start(args, format);
	va_copy(copy, args);

	/* calculate the length of the message + null terminator */
	size_t string_size = 1 + (size_t)vsnprintf(NULL, 0, format, copy);
	va_end(copy);

	/* allocate memory for the warning message */
	char *format_str = malloc(string_size);
	if (format_str == NULL)
	{
		fprintf(stderr, "malloc() call failed and returned NULL\n");
		free(format_str);
		exit(1);
	}

	vsnprintf(format_str, string_size, format, args);
	va_end(args);
	return format_str;
}
