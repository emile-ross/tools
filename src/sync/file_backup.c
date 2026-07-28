#include "header.h"

int fbackup(data_types backup_type)
{
	switch (backup_type)
	{
		case all_backup_opt:
		case gitconfig_data:
			backup_file(&gitconfig_files, &file_data);

			if (!(backup_type == all_backup_opt))
				break;
			else
				__attribute__ ((fallthrough));
		case passwords_data:
			backup_file(&passwords_files, &file_data);

			if (!(backup_type == all_backup_opt))
				break;
			else
				__attribute__ ((fallthrough));
		case mfa_auths_data:
			backup_file(&mfa_auth_backup, &file_data);
			backup_file(&aegis_backup, &file_data);

			if (!(backup_type == all_backup_opt))
				break;
			else
				__attribute__ ((fallthrough));
		case bookmarks_data:
			backup_file(&bookmarks_files, &file_data);

			if (!(backup_type == all_backup_opt))
				break;
			else
				__attribute__ ((fallthrough));
		case wifi_logs_data:
			backup_file(&wifi_logs_files, &file_data);

			if (!(backup_type == all_backup_opt))
				break;
			else
				__attribute__ ((fallthrough));
		case dns_logs_data:
			backup_file(&dns_logs_files, &file_data);

			if (!(backup_type == all_backup_opt))
				break;
			else
				__attribute__ ((fallthrough));
		default:
			break;
	}
	return 0;
}
