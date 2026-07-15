#define POSIX_C_SOURCE 199506L
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define min_args (3)
#define base_args (1)	/* the number of useless arguments preceeding the command (with info) */
typedef enum
{
	True = 1,
	False = 0
} Bool;

int main(int argc, char *argv[])
{
	Bool full_backup = True;
	if (argc > min_args)
	{
		uint8_t i = 0;
		for (; i < argc; i++)
		{
			if (strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "--all") == 0)
			{
				full_backup = False;
			}
		}
	}
	else
	{
		full_backup = False;
	}
	if (full_backup)
	{
		/* do full backup */
	}
	else
	{
		/* backup specific configs */
	}
	return 0;
}
