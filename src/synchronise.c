#define POSIX_C_SOURCE 200112L

#include <stdint.h>
#include <string.h>
#include "include/file_write.h"

#define min_args (1)
#define base_args (1)	/* the number of useless arguments preceeding the command (with info) */

typedef enum
{
	True = 1,
	False = 0
} Bool;

/* choose the name of your password database (including its path) */
const char passwords_file[16] = "passwords.kdbx";
const char bookmarks_file[16] = "bookmarks.json";
const char gitconfig_file[16] = ".gitconfig";

Bool use_home_dir = False;

const Bool verbose = True;

typedef struct
{
	Bool passwords;
	Bool bookmarks;
	Bool gitconfig;
	Bool wifi_logs;
} backup_data_type;

int backupfn(backup_data_type *dataBackup, char *home);

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

	char *home = NULL;
	if (use_home_dir)
	{
		home = bmalloc(getenv("HOME"));
		backupfn(pbackup, home);
	}
	else
	{
		if (verbose)
		{
			printf("verbose: Not using home directory\n");
		}
		backupfn(pbackup, NULL);
	}

	free(home);
	return 0;
}

int backup_data(char *home, char *filepath);

int backupfn(backup_data_type *dataBackup, char *home)
{
	Bool data_backed_up = False;	/* set to true whenever data has been backed up */
	if (dataBackup->gitconfig)
	{
		data_backed_up = True;
		char *file = bmalloc(gitconfig_file);
		backup_data(home, file);
		free(file);
	}

	if (dataBackup->bookmarks)
	{
		data_backed_up = True;
		char *file = bmalloc(bookmarks_file);
		backup_data(home, file);
		free(file);
	}

	if (dataBackup->passwords)
	{
		data_backed_up = True;
		char *file = bmalloc(passwords_file);
		backup_data(home, file);
		free(file);
	}
	else if (!data_backed_up)
	{
		fprintf(stderr, "No data was backed up\n");
		free(home);
		return 1;
	}

	return 0;
}

int backup_data(char *home, char *filepath)
{
	char *source_file = NULL;

	if (home == NULL)
	{
		source_file = bmalloc("%s", filepath);
	}
	else
	{
		source_file = bmalloc("%s/%s", home, filepath);
	}

	if (verbose)
	{
		printf("%s\n", source_file);
	}

	free(source_file);
	return 0;
}
