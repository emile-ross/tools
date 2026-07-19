#include "header.h"

/* frees an array of buffers backwards until it reaches the previous point (prev_i) */
int arrfree(uint16_t *buffer_i, uint16_t *prev_i, void *buf_array[])
{
	uint16_t buf_i = *buffer_i;
	while (buf_i > *prev_i)
	{
		buf_i--;
		if (buf_array[buf_i] != NULL)
		{
			free(buf_array[buf_i]);
			buf_array[buf_i] = NULL;
		}
		else
		{
			fprintf(stderr, "buf_array[] has a NULL pointer (freed)\n");
			return 1;
		}
	}
	*(buffer_i) = buf_i;
	return 0;
}

void free_buffers(void *buffers[])
{
	if (buffers != NULL)
	{
		uint8_t i = 0;
		for (; buffers[i] != NULL; i++)
		{
			free(buffers[i]);
			buffers[i] = NULL;
		}

		if (verbose)
		{
			verbose_print("Successfully freed %hhu buffers", i);
		}
	}
}
