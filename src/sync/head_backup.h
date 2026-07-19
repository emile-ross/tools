
int backup_data(char *src_filepath, char *dst_filepath);
int backup_file_conversion(void *buf_arr[], uint16_t *buffer_iterator, struct filename_type *filename_data);

/* in match_config.c */
int match_config(uint16_t buf_i, void *buf_arr[], Bool backup_data_arr[NUM_DATA_BACKUP], struct filename_type *filename_data);

