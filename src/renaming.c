#include <stdio.h>

/* this will rename files with certain characters in the filename */
int main(int argc, char *argv[])
{
	if (argc > 2)
	{
		if (strcmp("-c", argv[1]) == 0)
		{
		}
		else if (strcmp("--all", argv[1]) == 0 || strcmp("-a", argv[1]) == 0)
		{
			/* all files option */
		}
		else if (strcmp("-c", argv[1]) == 0)
		{
		}
	}
	else
	{
		/* this is not intended behaviour for now.. */
		return 1;
		printf("Provide the filename\n");
		/* get input */
	}

	return 0;
}
