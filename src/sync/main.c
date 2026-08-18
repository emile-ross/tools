#include "header.h"

#define min_args (1)
#define base_args (1)	/* the number of useless arguments preceeding the command (with info) */

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
				backup_args.path_bl = True;
				backup_args.path = get_path();
			}
			else if (cmp(argv[i], "-a", "--all"))
			{
				fbackup(all_backup_opt);
				break;	/* if we don't expect anything else */
			}
			else if (cmp(argv[i], "-2", "--2fa"))
			{
				backup_args[j] = mfa_auths_data;
				j++;
			}
			else if (cmp(argv[i], "-psw", "--passwords"))
			{
				backup_args[j] = passwords_data;
				j++;
			}
			else if (cmp(argv[i], "-d", "--dns"))
			{
				backup_args[j] = dns_logs_data;
				j++;
			}
			else if (cmp(argv[i], "-b", "--bookmarks"))
			{
				backup_args[j] = bookmarks_data;
				j++;
			}
			else if (cmp(argv[i], "-w", "--wifi"))
			{
				backup_args[j] = wifi_logs_data;
				j++;
			}
			else if (cmp(argv[i], "-n", "--nvim"))
			{
				backup_args[j] = nvim_conf_data;
				j++;
			}
			else if (cmp(argv[i], "-g", "--gitconfig") || scmp(argv[i], "--git"))
			{
				backup_args[j] = gitconfig_data;
				j++;
			}
			else if (cmp(argv[i], "-s", "--sway"))
			{
				backup_args[j] = sway_conf_data;
				j++;
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
