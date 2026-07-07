#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if (argc > 1)
	{
	}
	else
	{
		fprintf(stderr, "Missing arguments, specify the file source\n");
		return 1;
	}
	return 0;
}
