#include <stdio.h>


typedef enum
{
	undefined_flag = 0,
	char_flag,
	all_files_flag,
	single_file_flag,
	invalid_flag,
} flag_type;


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
