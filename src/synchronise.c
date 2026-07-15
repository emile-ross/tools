#define POSIX_C_SOURCE 200112L
#include <stdint.h>
#include <string.h>
#include "include/file_write.h"

#define min_args (1)
#define base_args (1)	/* the number of useless arguments preceeding the command (with info) */

/* choose the name of your password database (including its path) */
const char passwords_file[16] = ".passwords.kdbx";


typedef enum
{
	True = 1,
	False = 0
} Bool;

typedef struct
{
	Bool passwords;
	Bool bookmarks;
	Bool gitconfig;
	Bool wifi_logs;
} backup_data_type;

void backup_passwords(void);

int main(int argc, char *argv[])
{
	/* used to optimise checking by avoiding to check the entire struct */
	Bool full_backup = False;
	backup_data_type backup = { False, False, False, False };
	backup_data_type *pbackup = &backup;
	if (argc > min_args)
	{
		uint8_t i = 0;
		for (; i < argc; i++)
		{
			if (strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "--all") == 0)
			{
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
		}
	}
	else
	{
		full_backup = True;
	}
	if (full_backup)
	{
		/* do full backup */
		backup_passwords();
	}
	else
	{
		/* backup specific configs */
		if (backup.gitconfig)
		{
			char config_name[16] = ".gitconfig";
		}
		else if (backup.bookmarks)
		{
		}
	}
	return 0;
}

void backup_passwords(void)
{
	char home_directory[64] = "/home/dir/";
	char *source_file = bmalloc("%s%s", home_directory, passwords_file);

	printf("%s\n", source_file);
	free(source_file);
}
