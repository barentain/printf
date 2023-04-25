#include "main.h"

/**
 * handle_print - Function to print argument based on type
 * @fmt: Formatted string
 * @list: List of arguments
 * @index: index
 * @buffer: Buffer array
 * @flag: Identifies active flags
 * @width: Width.
 * @precision: Precision
 * @size: Size
 * Return: 1 or 2;
 */

int handle_print(const char *fmt, int *index, va_list list,
		char buffer[], int flag, int width, int precision, int size)
{
	int a, u_len = 0, char_print = -1;
	fmt_t fmt_types[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};
	for (a = 0; fmt_types[a].fmt != '\0'; a++)
		if (fmt[*index] == fmt_types[a].fmt)
			return (fmt_types[a].fn(list, buffer, flag, width, precision, size));

	if (fmt_types[a].fmt == '\0')
	{
		if (fmt[*index] == '\0')
			return (-1);
		u_len += write(1, "%%", 1);
		if (fmt[*index - 1] == ' ')
			u_len += write(1, " ", 1);
		else if (width)
		{
			--(*index);
			while (fmt[*index] != ' ' && fmt[*index] != '%')
				--(*index);
			if (fmt[*index] == ' ')
				--(*index);
			return (1);
		}
		u_len += write(1, &fmt[*index], 1);
		return (u_len);
	}
	return (char_print);
}
