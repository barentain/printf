#include "main.h"

/**
 * get_size - Function to calculate size of the argument
 * @format: Formatted string
 * @a: Arguments
 *
 * Return: Size
 */
int get_size(const char *format, int *a)
{
	int current = *a + 1, size = 0;

	if (format[current] == 'l')
		size = S_LONG;
	else if (format[current] == 'h')
		size = S_SHORT;

	if (size == 0)
		*a = current - 1;
	else
		*a = current;

	return (size);
}
