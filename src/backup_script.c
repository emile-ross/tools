#define POSIX_C_SOURCE 199506L
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define min_args (3)
typedef enum
{
	True = 1,
	False = 0
} Bool;

int main(int argc, char *argv[])
{
	Bool full_backup = True;
	if (argc > min_args)
	{
	}
	else
	{
		full_backup = False;
	}
	return 0;
}
