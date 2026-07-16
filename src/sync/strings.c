#include "header.h"

char *get_time_str(void)
{
	time_t default_time = time(NULL);
	struct tm *cur_time = localtime(&default_time);

	uint8_t day = (uint8_t)cur_time->tm_mday;
	uint8_t month = 1 + (uint8_t)cur_time->tm_mon;
	uint32_t year = 1900 + (uint32_t)cur_time->tm_year;

	return bmalloc("%u-%hhu-%hhu", year, month, day);
}

void verbose_print(const char *format, ...)
{
	va_list args;
	printf("\x1B[96m");	/* start a light cyan sequence */
	
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
	
	printf("\x1B[0m\n");	/* reset colour */
}
