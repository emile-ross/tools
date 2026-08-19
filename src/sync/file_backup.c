#include "header.h"

#define backup(file) \
	do { \
		backup_file(&(file)); \
		if (backup_type[i] != all_backup_opt) \
			return 0; \
		else \
			__attribute__ ((fallthrough)); \
	} while (0)

int fbackup(struct backup_args args, data_types (*backup_type)[])
{
	for (int i = 0; i <= args.num_args; i++)
	{
		switch (backup_type[i])
		{
		case all_backup_opt:
		case gitconfig_data:
			backup(gitconfig_files);
		case passwords_data:
			backup_file(&passwords_files);

			if (!(backup_type == all_backup_opt))
				break;
			else
				__attribute__ ((fallthrough));
		case mfa_auths_data:
			backup_file(&mfa_auth_backup);
			backup_file(&aegis_backup);

			if (!(backup_type == all_backup_opt))
				break;
			else
				__attribute__ ((fallthrough));
		case bookmarks_data:
			backup(bookmarks_files);
		case wifi_logs_data:
			backup(wifi_logs_files);
		case nvim_conf_data:
			backup_file(&nvim_conf_files);

			if (!(backup_type == all_backup_opt))
				break;
			else
				__attribute__ ((fallthrough));

		case dns_logs_data:
			backup_file(&dns_logs_files);

			if (!(backup_type == all_backup_opt))
				break;
			else
				__attribute__ ((fallthrough));
		case sway_conf_data:
			backup_file(&sway_conf_files);

			if (!(backup_type == all_backup_opt))
				break;
			else
				__attribute__ ((fallthrough));

		default:
			break;
		}
	}
	return 0;
}
