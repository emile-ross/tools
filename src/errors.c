#include <stdio.h>
#include <stdarg.h>

void err(const char *format, ...)
{
	va_list args;
	fprintf(stderr, "\x1b[31merror: ");	/* start a light cyan sequence */
	
	va_start(args, format);
	vfprintf(stderr, format, args);
	va_end(args);
	
	fprintf(stderr, "\x1B[0m\n");	/* reset colour */
}
