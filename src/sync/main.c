#include "header.h"

#define min_args (1)
#define base_args (1)	/* the number of useless arguments preceeding the command (with info) */

#define BACKUP_ARG(data) \
    do { \
        backup_args[j] = data; \
        j++; \
    } while (0)

int main(int argc, char *argv[])
{
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

	if (argc > min_args)
	{
		uint8_t i = base_args;

		struct backup_args BackupArgs = { False, NULL };
		
		uint8_t num_args = argc - min_args;
		data_types backup_args[num_args];
		uint8_t j = 0;


		for (; i < argc; i++)
		{
			if (cmp(argv[i], "-p", "--path"))
			{
				BackupArgs.path_bl = True;
				BackupArgs.path = get_path();
			}
			else if (cmp(argv[i], "-a", "--all"))
			{
				BACKUP_ARG(all_backup_opt);
			}
			else if (cmp(argv[i], "-2", "--2fa"))
			{
				BACKUP_ARG(mfa_auths_data);
			}
			else if (cmp(argv[i], "-psw", "--passwords"))
			{
				BACKUP_ARG(passwords_data);
			}
			else if (cmp(argv[i], "-d", "--dns"))
			{
				BACKUP_ARG(dns_logs_data);
			}
			else if (cmp(argv[i], "-b", "--bookmarks"))
			{
				BACKUP_ARG(bookmarks_data);
			}
			else if (cmp(argv[i], "-w", "--wifi"))
			{
				BACKUP_ARG(wifi_logs_data);
			}
			else if (cmp(argv[i], "-n", "--nvim"))
			{
				BACKUP_ARG(nvim_conf_data);
			}
			else if (cmp(argv[i], "-g", "--gitconfig") || scmp(argv[i], "--git"))
			{
				BACKUP_ARG(gitconfig_data);
			}
			else if (cmp(argv[i], "-s", "--sway"))
			{
				BACKUP_ARG(sway_conf_data);
			}
			else
			{
				verbose_print("%s flag ignored (unknown flag)\n", argv[i]);
			}
		}

	}
	else
	{
		fbackup(all_backup_opt);
	}

	return 0;
}
