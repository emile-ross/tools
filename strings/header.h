#include <stdbool.h>
#include <stdio.h>

struct args_type parse_args(const int num_args, const char *restrict args[]);
bool str_n_compare(const char *restrict arg, const char *restrict str, size_t size);

struct args_type
{
	const char *restrict target_directory;
	const char *restrict string;
	bool case_sensitive;
};
