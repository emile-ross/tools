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
	uint32_t total_words;
	uint32_t valid_words;
} word_list;

word_list parse_cmd(int num_args, char *arg[]);

int main(int argc, char *argv[])
{
	if (argc > 1)
	{
		parse_cmd(argc, argv);
	}
	else
	{
		fprintf(stderr, "Missing arguments, specify the file source\n");
		return 1;
	}
	return 0;
}
