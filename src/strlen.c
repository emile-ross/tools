#include <locale.h>
#include <stdlib.h>
#include <wchar.h>

size_t string_length(const char *string)
{
	mbstate_t state = {0};
	size_t len = 0;
	
	while (*string)
	{
		size_t n = mbrlen(string, MB_CUR_MAX, &state);
		
		/* invalid UTF-8 */
		if (n == (size_t)-1 || n == (size_t)-2)
			return (size_t)-1;
		
		if (n == 0)
			break;
		
		string += n;
		len++;
	}
	
	return len;
}
