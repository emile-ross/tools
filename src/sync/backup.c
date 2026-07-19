#include "header.h"
#include "head_backup.h"

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
	void *buf_arr[5] = { home, filename_data.time_string, NULL, NULL, NULL };
	uint8_t buf_i = 2;	/* iterator for the buf_arr */

	match_config(buf_i, buf_arr, backup_data_arr, &filename_data);
	free_buffers(buf_arr);

	return 0;
}

int backup_data(char *src_filepath, char *dst_filepath)
{
	char *source_file = NULL;
	char *dest_file = NULL;
	uint8_t buf_i = 0;
	void *buf_arr[3] = { NULL, NULL, NULL };

	source_file = bmalloc(buf_arr, "%s", src_filepath);
	buf_arr[buf_i] = source_file; buf_i++;
	dest_file = bmalloc(buf_arr, "%s", dst_filepath);
	buf_arr[buf_i] = dest_file; buf_i++;

	if (verbose)
	{
		verbose_print("Source file path: %s", source_file);
		verbose_print("Destination path: %s", dest_file);
	}

	if (!testing)
	{
		char *cmd = bmalloc(buf_arr, "cp %s %s", source_file, dest_file);
		if (verbose)
		{
			verbose_print("Backing up %s...", source_file);
		}

		printf("\x1B[91m\x1B[1m\n");	/* start a bold red sequence */

		system(cmd);

		printf("\x1B[0m");	/* reset colour */
		free(cmd);
	}


	free_buffers(buf_arr);

	return 0;
}

int backup_file_conversion(void *buf_arr[], uint16_t *buffer_iterator, struct filename_type *filename_data)
{
	/* set buffer iterators */
	uint16_t buf_i = *buffer_iterator;
	uint16_t prev_buf_i = buf_i;

	char *src_file = NULL;
	char *dst_file = NULL;

	if (filename_data->home_string != NULL)
	{
		char *home_path = "%s/%s";
		src_file = bmalloc(buf_arr, home_path, filename_data->home_string, 
				filename_data->source_filepath);
		dst_file = bmalloc(buf_arr, home_path, filename_data->home_string, 
				filename_data->time_string, filename_data->destination_filepath);
	}
	else
	{
		src_file = bmalloc(buf_arr, filename_data->source_filepath);
		dst_file = bmalloc(buf_arr, filename_data->destination_filepath, filename_data->time_string);
	}
	
	backup_data(src_file, dst_file);
	/* remove from buf_arr[] */
	buf_arr[buf_i] = src_file; buf_i++;
	buf_arr[buf_i] = dst_file; buf_i++;

	arrfree(&buf_i, &prev_buf_i, buf_arr);
	*(buffer_iterator) = buf_i;
	return 0;
}
