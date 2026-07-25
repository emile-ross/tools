#include <locale.h>
#include <wchar.h>

size_t string_length(const char *string)
{
	mbstate_t state = {0};
	size_t len = 0;
	size_t n;
	
	while (*string)
	{
		n = mbrlen(string, MB_CUR_MAX, &state);
		
		/* invalid UTF-8 */
		if (n == (size_t)-1 || n == (size_t)-2)
			return (size_t)-1;
		
		string += n;
		len++;
	}
	
	return len;
}
