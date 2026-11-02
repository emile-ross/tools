#include <stdio.h>
#include <dirent.h>

int main(void)
{
	DIR *cur = opendir(".");

	struct dirent *directory = NULL;

	do
	{
		/* reads the directory for a filename */
		directory = readdir(cur);
		if (directory != NULL)
			printf(directory->d_name);
		printf("\n");
	}
	while (directory != NULL);

	printf("\n");


	return 0;
}
