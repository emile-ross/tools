#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define UINT8MAX (255)
#define UINT16MAX (65535)
#define UINT32MAX (4294967295)
#define max_args (8)


/* my own implementation of the stdbool.h library (C99 extension) */
typedef enum
{
	True = 1,
	False = 0
} Bool;

const Bool verbose = False;

typedef struct
{
	char *source_file;
	char *output_file;
	Bool success;
	uint8_t letters_word;
	uint32_t total_words;
	uint32_t valid_words;
} word_list;

word_list parse_cmd(int num_args, char *arg[]);
void get_lines(word_list *list_args);
void get_words(word_list *list_args);

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
			if (verbose)
			{
				printf("%s: %u lines \n", list_args.source_file, list_args.total_words);
			}
		}

		get_words(&list_args);
		if (verbose)
		{
			printf("%s: %u valid words \n", list_args.output_file, list_args.valid_words);
		}
		else
		{
			printf("%u words were matching the length\n", list_args.valid_words);
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
	word_list word_list_qualifiers = { NULL, NULL, False, 0, 0, 0 };
	uint8_t i = 0;
	uint8_t base_arg_r = 1;
	uint16_t next = base_arg_r + 1;
	Bool implicit = False;
	long temp_input = 0;
	char *endptr;
	Bool used_args[max_args];

	for (i = base_arg_r; i < max_args; i++)
		used_args[i] = False;

	for (i = 0; i < base_arg_r; i++)
		used_args[i] = True;

	if (!(UINT16MAX >= num_args))
	{
		fprintf(stderr, "Too many arguments were specified");
		exit(1);
	}

	for (i = base_arg_r; i < num_args; i++)
	{
		if (strcmp(arg[i], "-s") == 0 || strcmp(arg[i], "-i") == 0)
		{
			used_args[i] = True;	/* argument is used up by a flag */
			implicit = False;
			if (!word_list_qualifiers.success)
			{
				if (num_args > next)
				{
					used_args[next] = True;	/* argument is used up by a flag */
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
			used_args[i] = True;	/* argument is used up by a flag */
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
				else
				{
					used_args[next] = True;	/* used up by the index */
					word_list_qualifiers.letters_word = (uint8_t)temp_input;
				}
			}
		}
		else if (strcmp(arg[i], "-o") == 0 || strcmp(arg[i], "--output") == 0)
		{
			used_args[i] = True;	/* argument is used up by a flag */
			if (num_args > next)
			{
				used_args[next] = True;	/* used up by the index */
				word_list_qualifiers.output_file = arg[next];
			}
			else
			{
				fprintf(stderr, "Expected filename after %s flag\n", arg[i]);
				exit(1);
			}
		}
		else
		{
			if (!used_args[i])
			{
				if (!word_list_qualifiers.success)
				{
					printf("Implicit use of %s as the filename\nUse -s for explicitly using it\n", arg[i]);
					word_list_qualifiers.source_file = arg[i];
					word_list_qualifiers.success = True;
					implicit = True;
				}
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

void get_words(word_list *list_args)
{
	/* allocate space for all words accounting for null terminator */
	char *buffer = malloc(list_args->total_words * (list_args->letters_word + 1));
	uint32_t valid_i = 0;
	char *dest;
	FILE *out;
	uint8_t i = 0;
	char temp[256];
	FILE *fp = fopen(list_args->source_file, "r");

	if (buffer == NULL || fp == NULL)
	{
		fclose(fp);
		exit(1);
	}

	while (valid_i < list_args->total_words && fscanf(fp, "%255s", temp) == 1)
	{
		if (strlen(temp) == list_args->letters_word)
		{
			dest = buffer + valid_i * (list_args->letters_word + 1);
			strncpy(dest, temp, (list_args->letters_word + 1));
			valid_i++;
		}
	}

	list_args->valid_words = valid_i;
	fclose(fp);
	

	if (list_args->output_file != NULL)
	{
		if (verbose)
		{
			printf("The words were written to %s\n", list_args->output_file);
		}

		out = fopen(list_args->output_file, "w");
		if (out == NULL)
		{
			free(buffer);
			exit(1);
		}
		
		for (i = 0; i < valid_i; i++)
		{
			fprintf(out, "%s\n", buffer + i * (list_args->letters_word + 1));
		}
		fclose(out);	
	}
	else
	{
		for (; i < valid_i; i++)
		{
			/* increment the pointer into the buffer by the number
			 * of letters in a word + 1 (NULL terminator) */
			printf("%s\n", buffer + i * (list_args->letters_word + 1));
		}
	}

	free(buffer);
}
