#include "header.h"

/* frees an array of buffers backwards until it reaches the previous point (prev_i) */
int arrfree(uint16_t buffer_i, uint16_t prev_i, void *buf_array[])
{
	while (buf_i > prev_buf_i)
	{
		buf_i--;
		if (buf_arr[buf_i] != NULL)
		{
			free(buf_arr[buf_i]);
			buf_arr[buf_i] = NULL;
		}
	}
}
