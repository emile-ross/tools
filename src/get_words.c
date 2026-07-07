#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define UINT8MAX (255)
#define UINT16MAX (65535)

/* my own implementation of the stdbool.h library (C99 extension) */
typedef enum
{
	True = 1,
	False = 0
} Bool;

typedef struct
{
	char *source_file;
	Bool success;
	uint8_t letters_word;
	uint32_t total_words;
	uint32_t valid_words;
} word_list;

word_list parse_cmd(int num_args, char *arg[]);
void file_reading(word_list *list_args);

int main(int argc, char *argv[])
{
	if (argc > 1)
	{
		word_list list_args = parse_cmd(argc, argv);
	}
	else
	{
		fprintf(stderr, "Missing arguments, specify the file source\n");
		return 1;
	}
	return 0;
}

word_list parse_cmd(int num_args, char *arg[])
{
	word_list word_list_qualifiers = { NULL, False, 0, 0, 0 };
	uint16_t i = 0;
	uint16_t next = i + 1;

	if (!(UINT16MAX >= num_args))
	{
		fprintf(stderr, "Too many arguments were specified");
		word_list_qualifiers.success = False;
		return word_list_qualifiers;
	}

	for (i = 0; i < num_args; i++)
	{
		if (strcmp(arg[i], "-s") == 0 || strcmp(arg[i], "-i") == 0)
		{
			if (!word_list_qualifiers.success)
			{
				if (num_args > next)
				{
					word_list_qualifiers.source_file = arg[next];
					word_list_qualifiers.success = True;
				}
				else
				{
					fprintf(stderr, "Expected filename after %s flag\n", arg[i]);
					word_list_qualifiers.success = False;
					return word_list_qualifiers;
				}
			}
			else
			{
				fprintf(stderr, "Duplicate use of the %s flag is not permitted\n", arg[i]);
				word_list_qualifiers.success = False;
				return word_list_qualifiers;
			}
		}
		else
		{
			if (!word_list_qualifiers.success)
			{
				printf("Implicit use of %s as the filename\nUse -s for explicitly using it\n", arg[i]);
				word_list_qualifiers.source_file = arg[i];
				word_list_qualifiers.success = True;
			}
		}

		next++;
	}
	return word_list_qualifiers;
}

