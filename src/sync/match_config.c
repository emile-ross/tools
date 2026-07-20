#include "header.h"

int match_config(void *buf_to_free, Bool backup_data_arr[NUM_DATA_BACKUP], struct filename_type *filename_data)
{
	Bool data_backed_up = False;

	if (backup_data_arr[gitconfig_data])
	{
		data_backed_up = True;
		filename_data->source_filepath = gitconfig_src;
		filename_data->destination_filepath = gitconfig_dst;
		backup_file_conversion(buf_to_free, filename_data);
	}

	if (backup_data_arr[dns_logs_data])
	{
		data_backed_up = True;

		filename_data->source_filepath = dns_logs_src;
		filename_data->destination_filepath = dns_logs_dst;
		backup_file_conversion(buf_to_free, filename_data);
	}

	if (backup_data_arr[bookmarks_data])
	{
		data_backed_up = True;
		filename_data->source_filepath = bookmarks_src;
		filename_data->destination_filepath = bookmarks_dst;
		backup_file_conversion(buf_to_free, filename_data);
	}

	if (backup_data_arr[passwords_data])
	{
		data_backed_up = True;
		filename_data->source_filepath = passwords_src;
		filename_data->destination_filepath = passwords_dst;
		backup_file_conversion(buf_to_free, filename_data);
	}
	else if (!data_backed_up)
	{
		fprintf(stderr, "No data was backed up\n");
		free(buf_to_free);
		return 1;
	}

	return 0;
}
