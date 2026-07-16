#define POSIX_C_SOURCE 200112L
#include <stdint.h>
#include <string.h>
#include "include/file_write.h"

#define min_args (1)
#define base_args (1)	/* the number of useless arguments preceeding the command (with info) */

/* choose the name of your password database (including its path) */
typedef enum
{
	True = 1,
	False = 0
} Bool;

const char passwords_file[16] = "passwords.kdbx";
Bool use_home_dir = False;
const char bookmarks_file[16] = "bookmarks.json";
const char gitconfig_file[16] = ".gitconfig";

Bool verbose = True;

typedef struct
{
	Bool passwords;
	Bool bookmarks;
	Bool gitconfig;
	Bool wifi_logs;
} backup_data_type;

void backup_passwords(char *home);

int main(int argc, char *argv[])
{
	/* used to optimise checking by avoiding to check the entire struct */
	backup_data_type backup = { False, False, False, False };
	backup_data_type *pbackup = &backup;	/* make a pointer to a struct & point to backup struct */

	/* this is just all set to true in order to make the process
	 * of setting everything to true easier */
	backup_data_type all_backup_struct = { True, True, True, True };

	if (argc > min_args)
	{
		uint8_t i = base_args;
		for (; i < argc; i++)
		{
			if (strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "--all") == 0)
			{
				pbackup = &all_backup_struct;
				break;	/* if we don't expect anything else */
			}
			else if (strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--passwords") == 0)
			{
				backup.passwords = True;
			}
			else if (strcmp(argv[i], "-b") == 0 || strcmp(argv[i], "--bookmarks") == 0)
			{
				backup.bookmarks = True;
			}
			else if (strcmp(argv[i], "-g") == 0 || strcmp(argv[i], "--gitconfig") == 0
					|| strcmp(argv[i], "--git") == 0)
			{
				backup.gitconfig = True;
			}
			else
			{
				printf("%s flag ignored (unknown flag)\n", argv[i]);
			}
		}
	}
	else
	{
		pbackup = &all_backup_struct;
	}

	char *home = bmalloc(getenv("HOME"));

	free(home);
	return 0;
}

void backup_gitconfig(char *home)
{
	char *source_file = bmalloc("%s%s", home, ".gitconfig");

	printf("%s\n", source_file);
	free(source_file);
}

void backup_bookmarks(char *home)
{
	char *source_file = bmalloc("%s%s", home, bookmarks_file);

	printf("%s\n", source_file);
	free(source_file);
}

int backupfn(backup_data_type *dataBackup, char *home)
{
	if (dataBackup->gitconfig)
	{
	}
	else if (dataBackup->bookmarks)
	{
	}
	else if (dataBackup->passwords)
	{
	}
	else
	{
		fprintf(stderr, "No data was backed up\n");
		free(home);
		return 1;
	}

	char *source_file = bmalloc("%s/%s", home, passwords_file);

	printf("%s\n", source_file);
	free(source_file);
	return 0;
}

int backup_data(char *home)
{
	char *source_file = NULL;

	if (home == NULL)
	{
		source_file = bmalloc("%s", passwords_file);
	}
	else
	{
		source_file = bmalloc("%s/%s", home, passwords_file);
	}

	if (verbose)
	{
		printf("%s\n", source_file);
	}

	free(source_file);
	return 0;
}
