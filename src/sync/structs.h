struct filename_type
{
	char *time_string;
	char *home_string;
	char *version_string;	/* unused */
	char *duplicate_string;	/* unused */
	char *custom_string;	/* unused */
};

struct filebackup_data
{
	char *source_filepath;
	char *destination_filepath;
	char *destination_directory;
	Bool dest_time_string;
	Bool src_home_string;
	Bool dest_home_string;
};

struct backup_args
{
	Bool path_bl;
	char *path;
	int8_t num_args;
};
