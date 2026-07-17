#include "header.h"

#define min_args (1)
#define base_args (1)	/* the number of useless arguments preceeding the command (with info) */

int main(int argc, char *argv[])
{
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
				verbose_print("%s flag ignored (unknown flag)\n", argv[i]);
			}
		}
	}
	else
	{
		pbackup = &all_backup_struct;
	}

	char *home = NULL;	/* will be allocated soon (maybe) */
	void *buf_arr[3] = { NULL, NULL, NULL };
	uint8_t buf_i = 0;

	if (use_home_dir_src)
	{
		if (verbose)
		{
			verbose_print("using home directory for source file\n");
		}

		char *home_dir = getenv("HOME");
		if (home_dir == NULL)
		{
			fprintf(stderr, "Failed to get home directory\n");
			return 1;
		}

		/* buf_arr will be NULL at this point 
		 * but this doesn't cause any unwanted problems */
		home = bmalloc(buf_arr, home_dir);
		buf_arr[buf_i] = home; buf_i++;

		backupfn(pbackup, home);
	}
	else
	{
		if (verbose)
		{
			verbose_print("Not using home directory for source file\n");
		}
		backupfn(pbackup, NULL);
	}

	free_buffers(buf_arr);
	return 0;
}
