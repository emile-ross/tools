#include "header.h"

int backup_data(char *home, char *src_filepath, char *dst_filepath);
int backup_file_conversion(void *buf_arr[], uint8_t *buffer_iterator, struct filename_type *filename_data);

int backupfn(Bool backup_data_arr[], char *home)
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

	Bool data_backed_up = False;	/* set to true whenever data has been backed up */

	filename_data.time_string = get_time_str();
	filename_data.home_string = home;
	void *buf_arr[5] = { home, filename_data.time_string, NULL, NULL, NULL };
	uint8_t buf_i = 2;	/* iterator for the buf_arr */

backup_data_arr[gitconfig_data]
backup_data_arr[wifi_logs_data]
	if (backup_data_arr[])
	{
		data_backed_up = True;
		filename_data.source_filepath = gitconfig_src;
		filename_data.destination_filepath = gitconfig_dst;
		backup_file_conversion(buf_arr, &buf_i, &filename_data);
	}

	if (backup_data_arr[bookmarks_data])
	{
		data_backed_up = True;
		filename_data.source_filepath = bookmarks_src;
		filename_data.destination_filepath = bookmarks_dst;
		backup_file_conversion(buf_arr, &buf_i, &filename_data);
	}

	if (backup_data_arr[passwords_data])
	{
		data_backed_up = True;
		filename_data.source_filepath = passwords_src;
		filename_data.destination_filepath = passwords_dst;
		backup_file_conversion(buf_arr, &buf_i, &filename_data);
	}
	else if (!data_backed_up)
	{
		fprintf(stderr, "No data was backed up\n");
		free(filename_data.time_string);
		return 1;
	}

	free(filename_data.time_string);
	return 0;
}

int backup_data(char *home, char *src_filepath, char *dst_filepath)
{
	char *source_file = NULL;
	char *dest_file = NULL;

	void *buf_arr[4] = { home, NULL, NULL, NULL };

	if (home == NULL)
	{
		source_file = bmalloc(buf_arr, "%s", src_filepath);
		dest_file = bmalloc(buf_arr, "%s", dst_filepath);
	}
	else
	{
		source_file = bmalloc(buf_arr, "%s/%s", home, src_filepath);
		dest_file = bmalloc(buf_arr, "%s/%s", home, dst_filepath);
	}

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

	free(source_file);
	free(dest_file);
	return 0;
}

int backup_file_conversion(void *buf_arr[], uint8_t *buffer_iterator, struct filename_type *filename_data)
{
	/* set buffer iterators */
	uint8_t buf_i = *buffer_iterator;
	const uint8_t prev_buf_i = buf_i;

	char *src_file = bmalloc(buf_arr, filename_data->source_filepath);
	char *dst_file = bmalloc(buf_arr, filename_data->destination_filepath, filename_data->time_string);

	/* remove from buf_arr[] */
	buf_arr[buf_i] = dst_file; buf_i++;
	buf_arr[buf_i] = src_file; buf_i++;

	while (buf_i > prev_buf_i)
	{
		free(buf_arr[buf_i]);
		buf_arr[buf_i] = NULL;
		buf_i--;
	}
	*(buffer_iterator) = buf_i;
	return 0;
}
