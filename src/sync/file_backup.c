#include "header.h"

int fbackup(struct filename_type *filename_data, data_types backup_type)
{
	switch (backup_type)
	{
		case all_backup_opt:
		case gitconfig_data:

			if (!(backup_type == all_backup_opt))
				break;
			else
				__attribute__ ((fallthrough));
		case passwords_data:
			backup_file(&passwords_backup, filename_data);

			if (!(backup_type == all_backup_opt))
				break;
			else
				__attribute__ ((fallthrough));
		case mfa_auths_data:
			backup_file(&mfa_auth_backup, filename_data);
			backup_file(&aegis_backup, filename_data);

			if (!(backup_type == all_backup_opt))
				break;
			else
				__attribute__ ((fallthrough));
		case bookmarks_data:

			if (!(backup_type == all_backup_opt))
				break;
			else
				__attribute__ ((fallthrough));
		case wifi_logs_data:

			if (!(backup_type == all_backup_opt))
				break;
			else
				__attribute__ ((fallthrough));
		case dns_logs_data:

			if (!(backup_type == all_backup_opt))
				break;
			else
				__attribute__ ((fallthrough));
		default:
			break;
	}
	return 0;
}
