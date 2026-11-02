#include <stdio.h>
#include <dirent.h>

int main(void)
{
	DIR *cur = opendir(".");

	struct dirent *directory = NULL;

	directory = readdir(cur)

	return 0;
}
