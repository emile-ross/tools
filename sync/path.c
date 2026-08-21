#include "header.h"

char *get_path(void)
{
	size_t max_length = 256;

	char *user_path = malloc(max_length);
	if (fgets(user_path, (int)max_length, stdin) == NULL) 
	{
		fprintf(stderr, "Failed to get the user path\n");
	}

	size_t length = 1 + strcspn(user_path, "\r\n\0");
	char *path = malloc(length);

	snprintf(path, length, "%s", user_path);
	free(user_path);

	return path;
}
