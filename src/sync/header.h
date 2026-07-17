#define POSIX_C_SOURCE 200112L

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

typedef struct
{
	Bool passwords;
	Bool bookmarks;
	Bool gitconfig;
	Bool wifi_logs;
} backup_data_type;

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
	char *get_time_str(void);

/* backup.c */
	int backupfn(backup_data_type *dataBackup, char *home);

