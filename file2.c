#include "main.h"
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>

/**
 * handle_d - Handles the %d and %i specifiers.
 * @args: A va_list of arguments.
 * @printed_chars: The total number of characters printed.
 * Return: The total number of characters printed.
 */
int handle_d(va_list args, int printed_chars)
{
    int num = va_arg(args, int);
    char num_str[12]; /* Assuming a maximum of 12 digits for an int */
    int len = snprintf(num_str, sizeof(num_str), "%d", num);
    write(1, num_str, len);
    printed_chars += len;
    return printed_chars;
}

/**
 * _printf - Produces output according to a format.
 * @format: A character string with format specifiers.
 * Return: The number of characters printed (excluding the null byte).
 */
int _printf(const char *format, ...)
{
    int printed_chars = 0;
    va_list args;

    va_start(args, format);

    while (*format)
    {
        if (*format != '%')
        {
            write(1, format, 1);
            printed_chars++;
        }
        else
        {
            format++;
            if (*format == 'c')
            {
                char c = va_arg(args, int);
                write(1, &c, 1);
                printed_chars++;
            }
            else if (*format == 's')
            {
                char *str = va_arg(args, char *);
                if (str)
                {
                    int len = 0;
                    while (str[len])
                        len++;
                    write(1, str, len);
                    printed_chars += len;
                }
                else
                {
                    write(1, "(null)", 6);
                    printed_chars += 6;
                }
            }
            else if (*format == '%')
            {
                write(1, "%", 1);
                printed_chars++;
            }
            else if (*format == 'd' || *format == 'i')
            {
                printed_chars = handle_d(args, printed_chars);
            }
        }
        format++;
    }

    va_end(args);

    return printed_chars;
}
