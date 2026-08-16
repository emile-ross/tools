#include "header.h"

int fbackup(data_types backup_type)
{
	switch (backup_type)
	{
		case all_backup_opt:
		case gitconfig_data:
			backup_file(&gitconfig_files);

			if (!(backup_type == all_backup_opt))
				break;
			else
				__attribute__ ((fallthrough));
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
			backup_file(&bookmarks_files);

			if (!(backup_type == all_backup_opt))
				break;
			else
				__attribute__ ((fallthrough));
		case wifi_logs_data:
			backup_file(&wifi_logs_files);

			if (!(backup_type == all_backup_opt))
				break;
			else
				__attribute__ ((fallthrough));
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
		default:
			break;
	}
	return 0;
}
