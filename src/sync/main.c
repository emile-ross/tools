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

	char *home_dir = getenv("HOME");
	if (home_dir == NULL)
	{
		err("Failed to get home directory");
		return 1;
	}
	file_data.time_string = get_time_str();
	file_data.home_string = home_dir;

	struct filename_type file_data =
	{
		NULL, NULL,
		get_time_str(),
		home_dir,
		NULL, NULL, NULL
	};

	if (argc > min_args)
	{
		uint8_t i = base_args;
		for (; i < argc; i++)
		{
			if (strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "--all") == 0)
			{
				fbackup(&file_data, all_backup_opt);
				break;	/* if we don't expect anything else */
			}
			else if (strcmp(argv[i], "-2") == 0 || strcmp(argv[i], "--2fa") == 0)
			{
				fbackup(&file_data, mfa_auths_data);
			}
			else if (strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--passwords") == 0)
			{
				fbackup(&file_data, passwords_data);
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

	/* the old way of archiving */
	backupfn(backup_data_arr, home_dir);

	return 0;
}



