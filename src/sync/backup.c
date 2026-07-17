#include "header.h"

int backup_data(char *home, char *src_filepath, char *dst_filepath);

int backupfn(backup_data_type *dataBackup, char *home)
{
	Bool data_backed_up = False;	/* set to true whenever data has been backed up */

	char *time_string = get_time_str();
	void *buf_arr[5] = { home, NULL, NULL, NULL, NULL };
	uint8_t buf_i = 1;	/* iterator for the buf_arr */
	uint8_t prev_buf_i = buf_i;

	if (dataBackup->gitconfig)
	{
		data_backed_up = True;

		/* allocate memory */
		char *src_file = bmalloc(buf_arr, gitconfig_src);
		char *dst_file = bmalloc(buf_arr, gitconfig_dst, time_string);

		/* add it in the buf_arr[] */
		buf_arr[buf_i] = dst_file; buf_i++;
		buf_arr[buf_i] = src_file; buf_i++;
		backup_data(home, src_file, dst_file);

		/* remove from buf_arr[] */
		while (buf_i > prev_buf_i)
		{
			free(buf_arr[buf_i]);
			buf_arr[buf_i] = NULL;
			buf_i--;
		}
	}

	if (dataBackup->bookmarks)
	{
		data_backed_up = True;
		char *src_file = bmalloc(buf_arr, bookmarks_src);
		char *dst_file = bmalloc(buf_arr, bookmarks_dst, time_string);

		buf_arr[buf_i] = dst_file; buf_i++;
		buf_arr[buf_i] = src_file; buf_i++;
		backup_data(home, src_file, dst_file);
		while (buf_i > prev_buf_i)
		{
			free(buf_arr[buf_i]);
			buf_arr[buf_i] = NULL;
			buf_i--;
		}
	}

	if (dataBackup->passwords)
	{
		data_backed_up = True;
		char *src_file = bmalloc(buf_arr, passwords_src);
		char *dst_file = bmalloc(buf_arr, passwords_dst, time_string);
		backup_data(home, src_file, dst_file);

		buf_arr[buf_i] = dst_file; buf_i++;
		buf_arr[buf_i] = src_file; buf_i++;
		while (buf_i > prev_buf_i)
		{
			free(buf_arr[buf_i]);
			buf_arr[buf_i] = NULL;
			buf_i--;
		}
	}
	else if (!data_backed_up)
	{
		fprintf(stderr, "No data was backed up\n");
		free(time_string);
		return 1;
	}

	free(time_string);
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
		dest_file = bmalloc(buf_arr, "%s/%s", home, dst_filepath);
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

int backup_file_conversion(void *buf_arr[], uint8_t *buffer_iterator, char source_file[], char destination_file[], char *time_string, char *home)
{
	uint8_t buf_i = *buffer_iterator;
	const uint8_t prev_buf_i = buf_i;

	char *src_file = bmalloc(buf_arr, source_file);
	char *dst_file = bmalloc(buf_arr, destination_file, time_string);
	backup_data(home, src_file, dst_file);

	buf_arr[buf_i] = dst_file; buf_i++;
	buf_arr[buf_i] = src_file; buf_i++;
	while (buf_i > prev_buf_i)
	{
		free(buf_arr[buf_i]);
		buf_arr[buf_i] = NULL;
		buf_i--;
	}
}
