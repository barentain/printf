#include "main.h"

/**
 * get_width - Function to calculate width
 * @format: Formatted string
 * @a: Arguments
 * @list: list of arguments.
 *
 * Return: Width
 */

int get_width(const char *format, int *a, va_list list)
{
	int current;
	int width = 0;

	for (current = *a + 1; format[current] != '\0'; current++)
	{
		if (is_digit(format[current]))
		{
			width *= 10;
			width += format[current] - '0';
		}
		else if (format[current] == '*')
		{
			current++;
			width = va_arg(list, int);
			break;
		}
		else
			break;
	}
	*a = current - 1;
	return (width);
}
