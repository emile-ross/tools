#include <stdarg.h>
#include <stdio.h>

size_t ssnprintf(char *buffer, size_t buffer_size, const char *format, ...)
{
	va_list ap;
	size_t return_value;
	
	va_start(ap, format);
	return_value = (size_t)vsnprintf(buffer, buffer_size, format, ap);
	va_end(ap);
	return return_value;
}
