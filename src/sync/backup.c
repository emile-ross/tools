#include "header.h"

int backupfn(Bool backup_data_arr[NUM_DATA_BACKUP], char *home)
{
	struct filename_type filename_data = 
	{
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL
	};

	filename_data.time_string = get_time_str();
	filename_data.home_string = home;

	match_config((void*)filename_data.time_string, backup_data_arr, &filename_data);

	free(filename_data.time_string);

	return 0;
}

int backup_data(char *src_filepath, char *dst_filepath)
{
	if (verbose)
	{
		verbose_print("Source file path: %s", src_filepath);
		verbose_print("Destination path: %s", dst_filepath);
	}

	if (!testing)
	{
		char *cmd = bmalloc(NULL, "cp %s %s", src_filepath, dst_filepath);
		if (verbose)
		{
			verbose_print("Backing up %s...", src_filepath);
		}

		printf("\x1B[91m\x1B[1m\n");	/* start a bold red sequence */

		system(cmd);

		printf("\x1B[0m");	/* reset colour */
		free(cmd);
	}

	return 0;
}

int backup_file_conversion(void *buf_to_free, struct filename_type *filename_data)
{
	/* set buffer iterators */

	char *src_file = NULL;
	char *dst_file = NULL;

	void *temp_mem_alloc[3] = { NULL, NULL, NULL };
	uint16_t buf_i = 0;

	void *buf_arr[2] = { buf_to_free, NULL };

	if (filename_data->home_string != NULL)
	{
		char *home_path = "%s/%s";
		src_file = bmalloc(*buf_arr, home_path, filename_data->home_string, 
				filename_data->source_filepath);
		temp_mem_alloc[buf_i] = src_file;
		buf_i++;
		char *dst_file_path = bmalloc(*buf_arr, home_path, filename_data->home_string, 
				filename_data->destination_filepath, filename_data->time_string);
		dst_file = bmalloc(*buf_arr, dst_file_path, filename_data->time_string);
		free(dst_file_path);
		temp_mem_alloc[buf_i] = dst_file;
		buf_i++;
	}
	else
	{
		src_file = bmalloc(*buf_arr, filename_data->source_filepath);
		dst_file = bmalloc(*buf_arr, filename_data->destination_filepath, filename_data->time_string);
	}
	
	backup_data(src_file, dst_file);

	free_buffers(temp_mem_alloc);
	return 0;
}
