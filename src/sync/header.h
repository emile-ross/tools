#define POSIX_C_SOURCE 200112L

#define NUM_DATA_BACKUP (4)

#include <stdint.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

typedef enum
{
	True = 1,
	False = 0
} Bool;

typedef enum
{
	gitconfig_data = 0,
	passwords_data,
	bookmarks_data,
	wifi_logs_data,
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

extern char *passwords_src;
extern char *passwords_dst;

extern char *bookmarks_src;
extern char *bookmarks_dst;

extern char *gitconfig_src;
extern char *gitconfig_dst;

extern char *wifi_logs_src;
extern char *wifi_logs_dst;

extern const Bool use_home_dir_src;
extern const Bool use_home_dir_dst;

extern const Bool verbose;
extern const Bool testing;

/* file_write.c */
	size_t ssnprintf(char *buffer, size_t buffer_size, const char *format, ...);
	char *bmalloc(void *bufs_to_free[], const char *format, ...);
	void free_buffers(void *buffers[]);

/* strings.c */
	void verbose_print(const char *format, ...);
	char *get_time_str(void *buf_to_free);

/* backup.c */
	int backupfn(Bool backup_data_arr[NUM_DATA_BACKUP], char *home);
	int backup_data(char *src_filepath, char *dst_filepath);
	int backup_file_conversion(void *buf_arr[], uint16_t *buffer_iterator, struct filename_type *filename_data);

/* mem.c */
	int arrfree(uint16_t *buffer_i, uint16_t *prev_i, void *buf_array[]);

/* in match_config.c */
	int match_config(uint16_t buf_i, void *buf_arr[], Bool backup_data_arr[NUM_DATA_BACKUP], struct filename_type *filename_data);

