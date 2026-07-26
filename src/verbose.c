#include <stdio.h>

void verbose_print(const char *format, ...)
{
	va_list args;
	printf("\x1B[96m");	/* start a light cyan sequence */
	
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
	
	printf("\x1B[0m\n");	/* reset colour */
}
