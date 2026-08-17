#include "header.h"

Bool cmp(char *argument, const char *short_flag, const char *long_flag)
{
	/* compare argument to the short flag 
	 * returns true if the argument matches the flag */
	if (strcmp(argument, short_flag) == 0)
	{
		return True;
	}

	/* compare argument to the long flag 
	 * returns true if the argument matches the flag */
	if (strcmp(argument, long_flag) == 0)
	{
		return True;
	}

	return False;
}

Bool scmp(char *argument, const char *flag)
{
	if (strcmp(argument, flag) == 0)
	{
		return True;
	}
	else
	{
		return False;
	}
}
