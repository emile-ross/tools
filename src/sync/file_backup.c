#include "header.h"

int fbackup(struct filebackup_data *filename_data, struct filename_type *file_data, data_types backup_type)
{
	switch (backup_type)
	{
		case all_backup_opt:
			__attribute__ ((fallthrough));	/* fallthrough **everything** */
		default:
			break;
	}
	return 0;
}
