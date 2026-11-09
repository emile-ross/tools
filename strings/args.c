#include "header.h"

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define CHECK_NEXT_ARG(FLAG) \
	if (i + 1 >= num_args) \
	{ \
		fprintf(stderr, "error: missing arguments following the %s flag\n", FLAG); \
		return ret; \
	}

#define OVERWRITE_WARN() \
	if (ret.string != NULL) \
		fprintf(stderr, "warning: overwriting old string \'%s\' with \'%s\'\n", ret.string, args[i]); \
	ret.string = args[i];

struct args_type parse_args(const int num_args, const char *restrict args[])
{
	struct args_type ret = { NULL, NULL, 0 };
	size_t len = 0;
	/* starting at 1 because we ignore the command executed */
	for (uint16_t i = 1; i < num_args; i++)
	{
		len = strlen(args[i]);
		if (str_n_compare(args[i], "-t", 3) || str_n_compare(args[i], "--target", len))
		{
			CHECK_NEXT_ARG(args[i]);
			ret.target_directory = args[i + 1];
			i++;
		}
		else if (str_n_compare(args[i], "-i", 3) || str_n_compare(args[i], "--insensitive", len))
		{
			ret.case_sensitive = false;
		}
		else if (str_n_compare(args[i], "-s", 3) || str_n_compare(args[i], "--string", len))
		{
			CHECK_NEXT_ARG(args[i]);
			i++;
			OVERWRITE_WARN();
		}
		else
		{
			OVERWRITE_WARN();
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
