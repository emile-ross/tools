#include "header.h"

#include <stdio.h>
#include <string.h>
#include <stdint.h>

struct args_type parse_args(const int num_args, const char *restrict args[])
{
	struct args_type ret = { NULL, NULL, 0 };
	size_t len = 0;	/* TODO use len in order to optimise string length comparaisons */
	for (uint16_t i = 0; i < num_args; i++)
	{
		len = strlen(args[i]);
		if (str_n_compare(args[i], "-t", 3) || str_n_compare(args[i], "--target", len))
		{
			if (i + 1 >= num_args)
			{
				fprintf(stderr, "error: missing args in command\n");
			}
			ret.target_directory = args[i + 1];
			i++;
		}
		else if (str_n_compare(args[i], "-i", 3) || str_n_compare(args[i], "--insensitive", len))
		{
			ret.case_sensitive = false;
		}
		else if (str_n_compare(args[i], "-s", 3) || str_n_compare(args[i], "--string", len))
		{
			printf("This is the string being parsed %s\n", args[i + 1]);
			i++;
		}
		else
		{
			printf("This is the string being parsed %s\n", args[i]);
		}
	}
	return ret;
}

bool scmp(const char *restrict arg, const char *restrict str)
{
	/* match arg to str */
	uint8_t i = 0;
	while (arg[i] != '\0' && str[i] != '\0')
	{
		if (arg[i] != str[i])
		{
			return false;
		}
		i++;
	}
	return true;
}

/* with size version */
bool str_n_compare(const char *restrict arg, const char *restrict str, size_t size)
{
	size_t i = 0;

	while (i < size)
	{
		if (arg[i] != str[i])
			return false;

		if (arg[i] == '\0')
			return true;

		i++;
	}
	return true;
}
