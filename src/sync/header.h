#define POSIX_C_SOURCE 200112L
#include "libs.h"

#include "../../include/verbose.h"
#include "../../include/errors.h"

#define NUM_DATA_BACKUP (6)

typedef enum
{
	True = 1,
	False = 0
} Bool;

typedef enum
{
	gitconfig_data = 0,
	passwords_data,
	mfa_auths_data,
	bookmarks_data,
	wifi_logs_data,
	dns_logs_data,
	all_backup_opt
} data_types;

struct filename_type
{
	char *source_filepath;
	char *destination_filepath;
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
	Bool dest_time_string;
	Bool src_home_string;
	Bool dest_home_string;
};

/* global variables */

	extern struct filename_type file_data;

	extern char *bookmarks_src;
	extern char *bookmarks_dst;
	
	extern char *gitconfig_src;
	extern char *gitconfig_dst;
	
	extern char *wifi_logs_src;
	extern char *wifi_logs_dst;

	extern char *dns_logs_src;
	extern char *dns_logs_dst;
	
	extern const Bool use_home_dir_src;
	extern const Bool use_home_dir_dst;
	
	extern const Bool verbose;
	extern const Bool testing;

/* file_write.c */
	size_t ssnprintf(char *buffer, size_t buffer_size, const char *format, ...);
	char *bmalloc(void *bufs_to_free[], const char *format, ...);
	void free_buffers(void *buffers[]);

/* strings.c */
	char *get_time_str(void);

/* backup.c */
	int backupfn(Bool backup_data_arr[NUM_DATA_BACKUP], char *home);
	int backup_data(char *src_filepath, char *dst_filepath);
	int backup_file_conversion(void *buf_to_free, struct filename_type *filename_data);

/* mem.c */
	void free_buffers(void *buffers[]);
	int arrfree(uint16_t *buffer_i, uint16_t *prev_i, void *buf_array[]);

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

	void backup_file(struct filebackup_data *filename_data, struct filename_type *file_data);


/* from src/sync/file_backup.c */
	int fbackup(struct filename_type *filename_data, data_types backup_type);
