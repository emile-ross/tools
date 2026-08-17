#include "header.h"

Bool cmp(char *argument, const char *short_flag, const char *long_flag)
{
	if (strcmp(argument, short_flag) == 0)
	{
		return True;
	}

	if (strcmp(argument, long_flag) == 0)
	{
		return True;
	}

	return False;
}
