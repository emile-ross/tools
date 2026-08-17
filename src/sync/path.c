#include "header.h"

char *get_path(void)
{
	size_t max_length = 256;

	char *user_path = malloc(max_length);
	if (fgets(user_path, (int)max_length, stdin) == NULL) 
	{
		fprintf(stderr, "Failed to get the user path\n");
	}
}
