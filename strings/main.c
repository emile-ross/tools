#include <stdio.h>
#include <inttypes.h>
#include <dirent.h>
#include <stdlib.h>

#define FILENAME_SIZE (256)

int main(void)
{
	DIR *cur = opendir(".");
	if (cur == NULL)
	{
		fprintf(stderr, "Failed to open current directory\n");
	}

	struct dirent *directory = NULL;
	size_t alloc_elements = 16;
	size_t element_increment = 2;	/* unused */
	size_t current_element = 0;

	char (*array)[256] = calloc(alloc_elements, FILENAME_SIZE);
	if (array == NULL)
	{
		fprintf(stderr, "malloc() function failed to allocate memory on the heap\n");
		return -1;
	}

	do
	{
		/* reads the directory for a filename */
		directory = readdir(cur);
		if (directory != NULL)
		{
			snprintf(array[current_element], FILENAME_SIZE, "%s", directory->d_name);
			current_element++;
		}
	}
	while (directory != NULL);

	for (size_t i = 0; i < current_element; i++)
	{
		printf("Element #%"PRIu64": %s\n", i, array[i]);
	}

	printf("\n");

	return 0;
}
