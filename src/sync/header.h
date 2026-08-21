#define POSIX_C_SOURCE 200112L
#include "libs.h"
#include "enums.h"
#include "structs.h"

#include "../../include/verbose.h"
#include "../../include/errors.h"

#define NUM_DATA_BACKUP (7)

/* global variables */
	extern struct filename_type file_data;

	extern const Bool verbose;
	extern const Bool testing;


/* file_write.c */
	size_t ssnprintf(char *buffer, size_t buffer_size, const char *format, ...);
	char *bmalloc(void *bufs_to_free[], const char *format, ...);
	void free_buffers(void *buffers[]);


/* strings.c */
	char *get_time_str(void);


/* mem.c */
	void free_buffers(void *buffers[]);
	int arrfree(uint16_t *buffer_i, uint16_t *prev_i, void *buf_array[]);


/* compare.c */
	Bool cmp(char *argument, const char *short_flag, const char *long_flag);
	Bool scmp(char *argument, const char *flag);


/* in match_config.c */
	int match_config(void *buf_to_free, Bool backup_data_arr[NUM_DATA_BACKUP], struct filename_type *filename_data);


/* new config.c */
	extern struct filebackup_data aegis_backup;
	extern struct filebackup_data bookmarks_files;
	extern struct filebackup_data dns_logs_files;
	extern struct filebackup_data gitconfig_files;
	extern struct filebackup_data mfa_auth_backup;
	extern struct filebackup_data passwords_files;
	extern struct filebackup_data wifi_logs_files;
	extern struct filebackup_data nvim_conf_files;
	extern struct filebackup_data sway_conf_files;

	void backup_file(struct filebackup_data *filename_data);

char *get_path(void);

/* from src/sync/file_backup.c */
	void file_check(char *directory);
	int fbackup(struct backup_args args, data_types (*backup_type)[]);
