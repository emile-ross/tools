#include "header.h"

#include <dirent.h>
#include <errno.h>

#define backup(file) \
		backup_file(&(file)); \
		if ((*backup_type)[i] != all_backup_opt) \
			break; \
		else \
			__attribute__ ((fallthrough)); \

int fbackup(struct backup_args args, data_types (*backup_type)[])
{
	if (verbose)
	{
		printf("%d args\n", args.num_args);
	}

	for (int i = 0; i <= args.num_args; i++)
	{
		switch ((*backup_type)[i])
		{
		case all_backup_opt:
		case gitconfig_data:
			backup(gitconfig_files);
		case passwords_data:
			backup(passwords_files);
		case mfa_auths_data:
			backup_file(&mfa_auth_backup);
			backup_file(&aegis_backup);

			if (!((*backup_type)[i] == all_backup_opt))
				break;
			else
				__attribute__ ((fallthrough));
		case bookmarks_data:
			backup(bookmarks_files);
		case wifi_logs_data:
			backup(wifi_logs_files);
		case nvim_conf_data:
			backup(nvim_conf_files);
		case dns_logs_data:
			backup(dns_logs_files);
		case sway_conf_data:
			backup(sway_conf_files);
		default:
			break;
		}
	}
	return 0;
}

Bool file_check(char *directory)
{
	DIR* dir = opendir(directory);
	if (dir)
	{
		closedir(dir);
		return True;
	}
	else if (ENOENT == errno) 
	{
		/* dir does not exist. */
		return False;
	}
	else
	{
		/* opendir() failed */
		fprintf(stderr, "opendir() function failed\n");
		exit(1);
	}
	return False;
}
