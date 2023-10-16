#include "main.h"
#include <stdarg.h>
#include <unistd.h>

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
            else if (*format == 'd' || *format == 'i')
            {
                int n = va_arg(args, int);
                int count = 0;
                int temp = n;
                while (temp != 0)
                {
                    temp /= 10;
                    count++;
                }
                if (n < 0)
                {
                    write(1, "-", 1);
                    printed_chars++;
                }
                while (count > 0)
                {
                    int divisor = 1;
                    for (int i = 1; i < count; i++)
                        divisor *= 10;
                    char digit = n / divisor + '0';
                    write(1, &digit, 1);
                    printed_chars++;
                    n %= divisor;
                    count--;
                }
            }
        }
        format++;
    }

    va_end(args);

    return printed_chars;
}
