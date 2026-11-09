#include "header.h"

#include <stdio.h>
#include <inttypes.h>
#include <dirent.h>
#include <stdlib.h>

#define FILENAME_SIZE (256)

int main(const int32_t argc, const char *restrict argv[])
{
	struct args_type args = parse_args(argc, argv);

	printf("string: %s\n", args.string);

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
		fprintf(stderr, "calloc() function failed to allocate memory on the heap\n");
		return -1;
	}

	do
	{
		/* reads the directory for a filename */
		directory = readdir(cur);
		/* TODO: check d_type for DT_CHR
		 * this DT_CHR means this file is
		 * actually a directory we can 
		 * recursively call check_dir()
		 * function in order to handle it */

		if (directory != NULL)
		{
			/* reallocate space on the array if we're out of bounds */
			if (current_element >= alloc_elements)
			{
				alloc_elements += element_increment;
				array = realloc(array, alloc_elements);
				element_increment <<= 1;
			}
			snprintf(array[current_element], FILENAME_SIZE, "%s", directory->d_name);
			current_element++;

			if (directory->d_type == DT_CHR)
			{
				/* TODO: recursively call check_dir() function */
			}
		}
	}
	while (directory != NULL);

	for (size_t i = 0; i < current_element; i++)
	{
		printf("Element #%"PRIu64": %s\n", i, array[i]);
	}


	free(array);

	return 0;
}
