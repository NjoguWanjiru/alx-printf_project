#include "main.h"
#include <unistd.h>
#include <stdarg.h>

/**
 * _printf - Produces output according to a format.
 * @format: A character string with format specifiers.
 * Return: the number of characters printed (excluding the null byte).
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
        }
        format++;
    }

    va_end(args);

    return printed_chars;
}
