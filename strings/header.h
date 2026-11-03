#include <stdbool.h>

struct args_type parse_args(const int num_args, const char *restrict args[]);
bool str_n_compare(const char *restrict arg, const char *restrict str, size_t size);

struct args_type
{
	char *target_directory;
	char *string;
	bool case_sensitive;
};
