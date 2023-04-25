#include "main.h"

/**
 * get_precision - function to calculate precision in printing
 * @format: Formatted string
 * @a: Arguments
 * @list: list of arguments.
 *
 * Return: Precision.
 */
int get_precision(const char *format, int *a, va_list list)
{
	int current = *a + 1;
	int precision = -1;

	if (format[current] != '.')
		return (precision);

	precision = 0;
	for (current += 1; format[current] != '\0'; current++)
	{
		if (is_digit(format[current]))
		{
			precision *= 10;
			precision += format[current] - '0';
		}
		else if (format[current] == '*')
		{
			current++;
			precision = va_arg(list, int);
			break;
		}
		else
			break;
	}
	*a = current - 1;

	return (precision);
}
