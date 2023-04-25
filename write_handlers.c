#include "main.h"

/**
 * handle_write_char - Function to print a string
 * @c: Char
 * @buffer: Buffer array to handle print
 * @flag: Calculates active flags.
 * @width: Width.
 * @precision: Precision
 * @size: Size
 *
 * Return: Number of chars printed.
 */

int handle_write_char(char c, char buffer[],
	int flag, int width, int precision, int size)
{
	int i = 0;
	char padding = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flag & F_ZERO)
		padding = '0';

	buffer[i++] = c;
	buffer[i] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			buffer[BUFF_SIZE - i - 2] = padding;

		if (flag & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - i - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - i - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/**
 * write_number - Prints a string
 * @is_negative: List of arguments
 * @index: Char
 * @buffer: Buffer array to handle print
 * @flag: Identifies active flags
 * @width: Width.
 * @precision: Precision
 * @size: Size
 *
 * Return: Number of chars printed.
 */
int write_number(int is_negative, int index, char buffer[],
	int flag, int width, int precision, int size)
{
	int length = BUFF_SIZE - index - 1;
	char padding = ' ', excess_char = 0;

	UNUSED(size);

	if ((flag & F_ZERO) && !(flag & F_MINUS))
		padding = '0';
	if (is_negative)
		excess_char = '-';
	else if (flag & F_PLUS)
		excess_char = '+';
	else if (flag & F_SPACE)
		excess_char = ' ';

	return (write_num(index, buffer, flag, width, precision, length,
				padding, excess_char));
}

/**
 * write_num - Function to write a number using a bufffer
 * @index: Index at which the number starts on the buffer
 * @buffer: Buffer
 * @flag: Flag
 * @width: Width
 * @precision: Precision
 * @length: Number length
 * @padding: Padding
 * @excess_char: Extra char
 *
 * Return: Number of printed chars.
 */

int write_num(int index, char buffer[], int flag, int width,
		int precision, int length, char padding, char excess_char)
{
	int i, padding_start = 1;

	if (precision == 0 && index == BUFF_SIZE - 2 &&
			buffer[index] == '0' && width == 0)
		return (0);
	if (precision == 0 && index == BUFF_SIZE - 2 && buffer[index] == '0')
		buffer[index] = padding = ' ';
	if (precision > 0 && precision < length)
		padding = ' ';
	while (precision > length)
		buffer[--index] = '0', length++;
	if (excess_char != 0)
		length++;
	if (width > length)
	{
		for (i = 1; i < width - length + 1; i++)
			buffer[i] = padding;
		buffer[i] = '\0';
		if (flag & F_MINUS && padding == ' ')
		{
			if (excess_char)
				buffer[--index] = excess_char;
			return (write(1, &buffer[index], length) + write(1, &buffer[1], i - 1));
		}
		else if (!(flag & F_MINUS) && padding == ' ')
		{
			if (excess_char)
				buffer[--index] = excess_char;
			return (write(1, &buffer[1], i - 1) + write(1, &buffer[index], length));
		}
		else if (!(flag & F_MINUS) && padding == '0')
		{
			if (excess_char)
				buffer[--padding_start] = excess_char;
			return (write(1, &buffer[padding_start], i - padding_start) +
				write(1, &buffer[index], length - (1 - padding_start)));
		}
	}
	if (excess_char)
		buffer[--index] = excess_char;
	return (write(1, &buffer[index], length));
}

/**
 * write_unsgnd - Function to wite an unsigned number
 * @is_negative: Number indicating if the num is negative
 * @index: Index at which the number starts in the buffer
 * @buffer: Array of chars
 * @flag: Flags
 * @width: Width
 * @precision: Precision
 * @size: Size
 *
 * Return: Number of written chars.
 */

int write_unsgnd(int is_negative, int index, char buffer[],
	int flag, int width, int precision, int size)
{
	int length = BUFF_SIZE - index - 1, i = 0;
	char padding = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && index == BUFF_SIZE - 2 && buffer[index] == '0')
		return (0);

	if (precision > 0 && precision < length)
		padding = ' ';

	while (precision > length)
	{
		buffer[--index] = '0';
		length++;
	}
	if ((flag & F_ZERO) && !(flag & F_MINUS))
		padding = '0';

	if (width > length)
	{
		for (i = 0; i < width - length; i++)
			buffer[i] = padding;

		buffer[i] = '\0';

		if (flag & F_MINUS)
		{
			return (write(1, &buffer[index], length) + write(1, &buffer[0], i));
		}
		else
		{
			return (write(1, &buffer[0], i) + write(1, &buffer[index], length));
		}
	}
	return (write(1, &buffer[index], length));
}

/**
 * write_pointer - Function to write a memory address
 * @buffer: Arrays of chars
 * @index: Index at which the number starts in the buffer
 * @length: Length of number
 * @width: Width specifier
 * @flag: Flags specifier
 * @padding: Char representing the padding
 * @excess_char: Char representing extra char
 * @padding_start: Index at which padding should start
 *
 * Return: Number of written chars.
 */
int write_pointer(char buffer[], int index, int length,	int width,
		int flag, char padding, char excess_char, int padding_start)
{
	int i;

	if (width > length)
	{
		for (i = 3; i < width - length + 3; i++)
			buffer[i] = padding;
		buffer[i] = '\0';
		if (flag & F_MINUS && padding == ' ')
		{
			buffer[--index] = 'x';
			buffer[--index] = '0';
			if (excess_char)
				buffer[--index] = excess_char;
			return (write(1, &buffer[index], length) + write(1, &buffer[3], i - 3));
		}
		else if (!(flag & F_MINUS) && padding == ' ')
		{
			buffer[--index] = 'x';
			buffer[--index] = '0';
			if (excess_char)
				buffer[--index] = excess_char;
			return (write(1, &buffer[3], i - 3) + write(1, &buffer[index], length));
		}
		else if (!(flag & F_MINUS) && padding == '0')
		{
			if (excess_char)
				buffer[--padding_start] = excess_char;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padding_start], i - padding_start) +
				write(1, &buffer[index], length - (1 - padding_start) - 2));
		}
	}
	buffer[--index] = 'x';
	buffer[--index] = '0';
	if (excess_char)
		buffer[--index] = excess_char;
	return (write(1, &buffer[index], BUFF_SIZE - index - 1));
}
