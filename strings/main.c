#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>

#define FILENAME_SIZE (256)

int main(void)
{
	DIR *cur = opendir(".");

	struct dirent *directory = NULL;
	size_t alloc_elements = 16;
	size_t element_increment = 2;	/* unused */
	size_t current_element = 0;

	char *(array[256]) = malloc(alloc_elements * FILENAME_SIZE);
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
			printf("%s\n", directory->d_name);
		}
		printf("\n");
	}
	while (directory != NULL);

	printf("\n");


	return 0;
}
