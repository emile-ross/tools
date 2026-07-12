#include <stdio.h>
#include <stdint.h>
#include <string.h>

/* the max number of arguments that can be specified per command */
#define max_args 16

typedef enum
{
	undefined_flag = 0,
	char_flag,
	all_files_flag,
	single_file_flag,
	invalid_flag
} flag_type;

typedef enum
{
	True = 1,
	False = 0
} Bool;

typedef struct 
{
	Bool use_all_files;
	char prev_char;
	char new_char;
} all_files_opt;

/* this will rename files with certain characters in the filename */
int main(int argc, char *argv[])
{
	if (argc > 2)
	{
		uint8_t i = 0;
		uint8_t next_index = i + 1;

		flag_type command_flag_types[max_args];
		for (; i < argc; i++)
		{
			if (strcmp("-r", argv[i]) == 0 || strcmp("--replace", argv[i]) == 0)
			{
				command_flag_types[i] = char_flag;

				if (next_index > argc)
				{
					fprintf(stderr, "Missing arguments after %s\nExpected character to replace\n", argv[i]);
					return 1;
				}
			}
			else if (strcmp("-c", argv[i]) == 0 || strcmp("--character", argv[i]) == 0)
			{
				command_flag_types[i] = char_flag;

				if (next_index > argc)
				{
					fprintf(stderr, "Missing arguments after %s\nExpected the new characters\n", argv[i]);
					return 1;
				}
			}
			else if (strcmp("--all", argv[i]) == 0 || strcmp("-a", argv[i]) == 0)
			{
				/* all files option */
				command_flag_types[i] = all_files_flag;
			}
			else if (strcmp("-s", argv[i]) == 0)
			{
				command_flag_types[i] = single_file_flag;
			}
			else
			{
				if (command_flag_types[i] == undefined_flag || command_flag_types[i] == invalid_flag)
				{
					command_flag_types[i] = invalid_flag;
				}
			}
			next_index++;
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
