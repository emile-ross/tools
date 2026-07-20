#include "header.h"

#define min_args (1)
#define base_args (1)	/* the number of useless arguments preceeding the command (with info) */

int main(int argc, char *argv[])
{
	Bool backup_data_arr[NUM_DATA_BACKUP];
	
	for (uint8_t i = 0; i < NUM_DATA_BACKUP; i++)
	{
		backup_data_arr[i] = False;
	}

	/* this is just all set to true in order to make the process
	 * of setting everything to true easier */

	if (argc > min_args)
	{
		uint8_t i = base_args;
		for (; i < argc; i++)
		{
			if (strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "--all") == 0)
			{
				for (uint8_t j = 0; j < NUM_DATA_BACKUP; j++)
				{
					backup_data_arr[j] = True;
				}
				break;	/* if we don't expect anything else */
			}
			else if (strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--passwords") == 0)
			{
				backup_data_arr[passwords_data] = True;
			}
			else if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--dns") == 0)
			{
				backup_data_arr[dns_logs_data] = True;
			}
			else if (strcmp(argv[i], "-b") == 0 || strcmp(argv[i], "--bookmarks") == 0)
			{
				backup_data_arr[bookmarks_data] = True;
			}
			else if (strcmp(argv[i], "-w") == 0 || strcmp(argv[i], "--wifi") == 0)
			{
				backup_data_arr[wifi_logs_data] = True;
			}
			else if (strcmp(argv[i], "-g") == 0 || strcmp(argv[i], "--gitconfig") == 0
					|| strcmp(argv[i], "--git") == 0)
			{
				backup_data_arr[gitconfig_data] = True;
			}
			else
			{
				verbose_print("%s flag ignored (unknown flag)\n", argv[i]);
			}
		}
	}
	else
	{
		for (uint8_t j = 0; j < NUM_DATA_BACKUP; j++)
		{
			backup_data_arr[j] = True;
		}
	}

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

		backupfn(backup_data_arr, home_dir);
	}
	else
	{
		if (verbose)
		{
			verbose_print("Not using home directory for source file\n");
		}
		backupfn(backup_data_arr, NULL);
	}

	return 0;
}
