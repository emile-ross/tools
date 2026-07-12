
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define max_args 16

typedef enum
{
	undefined_flag = 0,
	char_flag,
	all_files_flag,
	single_file_flag,
	invalid_flag
} flag_type;

/* this will rename files with certain characters in the filename */
int main(int argc, char *argv[])
{
	if (argc > 2)
	{
		uint8_t i = 0;
		flag_type command_flag_types[max_args];
		for (; i < argc; i++)
		{
			if (strcmp("-c", argv[i]) == 0)
			{
				command_flag_types[i] = char_flag;
			}
			else if (strcmp("--all", argv[i]) == 0 || strcmp("-a", argv[i]) == 0)
			{
				/* all files option */
				command_flag_types[i] = all_files_flag;
			}
			else if (strcmp("-c", argv[i]) == 0)
			{
			}
			else if (strcmp("-s", argv[i]) == 0)
			{
				command_flag_types[i] = single_file_flag;
			}
			else
			{
				command_flag_types[i] = invalid_flag;
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
