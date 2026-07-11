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
		uint8_t i = 0;
		flag_type command_flag_types[argc];
		for (; i < argc; i++)
		{
			if (strcmp("-c", argv[1]) == 0)
			{
				command_flag_types = char_flag;
			}
			else if (strcmp("--all", argv[1]) == 0 || strcmp("-a", argv[1]) == 0)
			{
				/* all files option */
				command_flag_types = all_files_flag;
			}
			else if (strcmp("-s", argv[1]) == 0)
			{
				command_flag_types = single_file_flag;
			}
			else
			{
				command_flag_types = invalid_flag;
			}
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
