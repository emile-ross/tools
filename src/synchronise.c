#define POSIX_C_SOURCE 200112L

#include <stdint.h>
#include <string.h>
#include <time.h>
#include "include/file_write.h"

#define min_args (1)
#define base_args (1)	/* the number of useless arguments preceeding the command (with info) */

typedef enum
{
	True = 1,
	False = 0
} Bool;

/* choose the name of your password database (including its path) */
const char passwords_src[16] = "passwords.kdbx";
const char passwords_dst[48] = "backup/passwords/%s-passwords.kdbx";

const char bookmarks_src[16] = "bookmarks.json";
const char bookmarks_dst[32] = "backup/%s-bookmarks.json";

const char gitconfig_src[16] = ".gitconfig";
const char gitconfig_dst[32] = "backup/git/.%s-gitconfig";

const char wifi_logs_src[24] = "logs/wifi_log.log";
const char wifi_logs_dst[24] = "backup/logs/%s-wifi.log";

Bool use_home_dir_src = True;
Bool use_home_dir_dst = True;

const Bool verbose = True;

typedef struct
{
	Bool passwords;
	Bool bookmarks;
	Bool gitconfig;
	Bool wifi_logs;
} backup_data_type;

int backupfn(backup_data_type *dataBackup, char *home);
char *get_time_str(void);

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
	if (use_home_dir_src)
	{
		if (verbose)
		{
			printf("verbose: using home directory for source file\n");
		}

		home = bmalloc(getenv("HOME"));
		backupfn(pbackup, home);
	}
	else
	{
		if (verbose)
		{
			printf("verbose: Not using home directory for source file\n");
		}
		backupfn(pbackup, NULL);
	}

	free(home);
	return 0;
}


int backupfn(backup_data_type *dataBackup, char *home)
{
	Bool data_backed_up = False;	/* set to true whenever data has been backed up */
	if (dataBackup->gitconfig)
	{
		data_backed_up = True;
		char *file = bmalloc(gitconfig_src);
		backup_data(home, file);
		free(file);
	}

	if (dataBackup->bookmarks)
	{
		data_backed_up = True;
		char *file = bmalloc(bookmarks_src);
		backup_data(home, file);
		free(file);
	}

	if (dataBackup->passwords)
	{
		data_backed_up = True;
		char *file = bmalloc(passwords_src);
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

int backup_data(char *home, char *src_filepath, char *dst_filepath)
{
	char *source_file = NULL;
	char *dest_file = NULL;

	if (home == NULL)
	{
		source_file = bmalloc("%s", src_filepath);
		dest_file = bmalloc("%s/%s", home, dst_filepath);
	}
	else
	{
		source_file = bmalloc("%s/%s", home, src_filepath);
		dest_file = bmalloc("%s/%s", home, dst_filepath);
	}

	if (verbose)
	{
		printf("%s\n", source_file);
	}

	free(source_file);
	free(dest_file);
	return 0;
}

char *get_time_str(void)
{
	time_t default_time = time(NULL);
	struct tm *cur_time = localtime(&default_time);

	uint8_t day = (uint8_t)cur_time->tm_mday;
	uint8_t month = 1 + (uint8_t)cur_time->tm_mon;
	uint32_t year = 1900 + (uint32_t)cur_time->tm_year;
	return bmalloc("%u-%hhu-%hhu", year, month, day);
}
