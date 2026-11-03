#include <stdio.h>
#include <string.h>

struct args_type parse_args(const int num_args, const *restrict char args)
{

	for (uint16_t i = 0; i < num_args; i++)
	{
		scmp
	}
}

bool scmp(const char *arg, const char *str)
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

