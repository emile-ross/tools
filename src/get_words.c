#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define UINT8MAX (255)
#define UINT16MAX (65535)
#define UINT32MAX (4294967295)

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
void get_lines(word_list *list_args);

int main(int argc, char *argv[])
{
	if (argc > 1)
	{
		word_list list_args = parse_cmd(argc, argv);
		get_lines(&list_args);
		/* only print the number of lines in the target file
		 * if the operation was successful */
		if (list_args.success)
		{
			printf("%u lines \n", list_args.total_words);
		}
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
	uint16_t i = 1;
	uint16_t next = i + 1;
	Bool implicit = False;
	long temp_input = 0;
	char *endptr;

	if (!(UINT16MAX >= num_args))
	{
		fprintf(stderr, "Too many arguments were specified");
		exit(1);
	}

	for (; i < num_args; i++)
	{
		if (strcmp(arg[i], "-s") == 0 || strcmp(arg[i], "-i") == 0)
		{
			implicit = False;
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
					exit(1);
				}
			}
			else if (!implicit)
			{
				fprintf(stderr, "Duplicate use of the %s flag is not permitted\n", arg[i]);
				exit(1);
			}
		}
		else if (strcmp(arg[i], "-l") == 0 || strcmp(arg[i], "--length") == 0)
		{
			if (num_args > next)
			{
				temp_input = strtol(arg[next], &endptr, 10);
				if (temp_input > UINT8MAX)
				{
					fprintf(stderr, "Invalid word length %ld is larger than %d\n", temp_input, UINT8MAX);
					exit(1);
				}
				else if (temp_input <= 0)
				{
					fprintf(stderr, "Word length cannot be zero\n");
					exit(1);
				}
				word_list_qualifiers.letters_word = (uint8_t)temp_input;
				i++;
			}
		}
		else
		{
			if (!word_list_qualifiers.success)
			{
				printf("Implicit use of %s as the filename\nUse -s for explicitly using it\n", arg[i]);
				word_list_qualifiers.source_file = arg[i];
				word_list_qualifiers.success = True;
				implicit = True;
			}
		}
		next++;
	}
	return word_list_qualifiers;
}

void get_lines(word_list *list_args)
{
	FILE *fp;
	uint64_t line_count = 0;

	char char_read = '\0';
	if (list_args->source_file == NULL)
	{
		fprintf(stderr, "Unspecified file path\n");
		exit(1);
	}

	fp = fopen(list_args->source_file, "r");
	/* checks if the file can be opened and if it exists */
	if (fp == NULL)
	{
		fprintf(stderr, "No such file or directory\n");
		exit(1);
	}

	for (char_read = (char)fgetc(fp); char_read != EOF; char_read = (char)fgetc(fp))
	{
		if (char_read == '\n')    
		{
			line_count++;
		}
	}

	/* count the last line even though it might end in EOF instead of \n */
	if (line_count > 0 || fgetc(fp) != EOF)
	{
		line_count++;
	}

	if (line_count == 0)
	{
		fprintf(stderr, "No lines in the file\n");
		exit(1);
	}

	if (UINT32MAX < line_count)
	{
		fprintf(stderr, "Too many lines in the file\n");
		fprintf(stderr, "Max lines: %ld\n", UINT32MAX);
		exit(1);
	}

	/* write the line_count to the list_args struct */
	list_args->total_words = (uint32_t)line_count;

	fclose(fp);
}
