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
		for (; i < argc; i++)
		{
			if (cmp(argv[i], "-p", "--path"))
			{
			}
			else if (cmp(argv[i], "-a", "--all"))
			{
				fbackup(all_backup_opt);
				break;	/* if we don't expect anything else */
			}
			else if (cmp(argv[i], "-2", "--2fa"))
			{
				fbackup(mfa_auths_data);
			}
			else if (cmp(argv[i], "-psw", "--passwords"))
			{
				fbackup(passwords_data);
			}
			else if (cmp(argv[i], "-d", "--dns"))
			{
				fbackup(dns_logs_data);
			}
			else if (cmp(argv[i], "-b", "--bookmarks"))
			{
				fbackup(bookmarks_data);
			}
			else if (cmp(argv[i], "-w", "--wifi"))
			{
				fbackup(wifi_logs_data);
			}
			else if (cmp(argv[i], "-n", "--nvim"))
			{
				fbackup(nvim_conf_data);
			}
			else if (cmp(argv[i], "-g", "--gitconfig") || strcmp(argv[i], "--git") == 0)
			{
				fbackup(gitconfig_data);
			}
			else if (cmp(argv[i], "-s", "--sway"))
			{
				fbackup(sway_conf_data);
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
