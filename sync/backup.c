#include "header.h"

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
			verbose_print("Executing: \"%s\"", cmd);
		}

		printf("\x1B[91m\x1B[1m\n");	/* start a bold red sequence */

		system(cmd);	/* execute the command created */

		printf("\x1B[0m");	/* reset colour */
		free(cmd);
	}

	return 0;
}

void backup_file(struct filebackup_data *filename_data)
{
	char *home_path = "%s/%s";
	char *backup_home_path = "%s/backup/%s";

	char *file_path = bmalloc(NULL, "%s/%s/%s", file_data.home_string, "backup", filename_data->destination_directory);
	if (!(file_check(file_path)))
	{
		char *command = bmalloc(NULL, "mkdir -p %s", file_path);
		system(command);
		free(command);
	}
	free(file_path);

	char *src_file = NULL;
	char *dst_file = NULL;

	if (filename_data->src_home_string)
	{
		src_file = bmalloc(NULL, home_path, file_data.home_string, 
				filename_data->source_filepath);
	}
	else
	{
		src_file = bmalloc(NULL, filename_data->source_filepath);
	}
	
	if (filename_data->dest_home_string)
	{
		char *dst_file_path = bmalloc(NULL, backup_home_path, file_data.home_string, 
				filename_data->destination_filepath);
		if (filename_data->dest_time_string)
		{
			dst_file = bmalloc(NULL, dst_file_path, file_data.time_string);
			free(dst_file_path);
		}
		else
		{
			dst_file = dst_file_path;
		}
	}
	else
	{
		if (filename_data->dest_time_string)
		{
			dst_file = bmalloc(NULL, filename_data->destination_filepath, file_data.time_string);
		}
		else
		{
			dst_file = bmalloc(NULL, filename_data->destination_filepath);
		}
	}

	backup_data(src_file, dst_file);

	if (dst_file != NULL)
		free(dst_file);
	if (src_file != NULL)
		free(src_file);
}
