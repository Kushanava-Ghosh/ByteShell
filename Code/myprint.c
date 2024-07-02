#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include "myprint.h"

void myprint_char(char c);
void myprint_int(int num);
void myprint_string(const char* str);


void myprint(const char* format, ...) {
    va_list args;
    va_start(args, format);

    while (*format) {
        if (*format == '%') {
            format++;

            switch (*format) {
                case 'c':
                    myprint_char((char) va_arg(args, int));
                    break;
                case 'd':
                    myprint_int(va_arg(args, int));
                    break;
                case 's':
                    myprint_string(va_arg(args, const char*));
                    break;
                
                default:
                    myprint_char(*format);
                    break;
            }
        } else {
            myprint_char(*format);
        }

        format++;
    }

    va_end(args);
}

void myprint_char(char c) {
    putchar(c);
}

void myprint_int(int num) {
        // Convert integer to a string representation
    char str[22];
    int i = 0;
    int is_negative = 0;

    if (num == 0) {
        myprint_char('0');
        return;
    }

    if (num < 0) {
        is_negative = 1;
        num = -num;
    }

    while (num != 0) {
        int digit = num % 10;
        str[i++] = digit + '0';
        num /= 10;
    }

    if (is_negative)
        myprint_char('-');

    for (int j = i - 1; j >= 0; j--)
        myprint_char(str[j]);

}

void myprint_string(const char* str) {
    int i = 0;
    while (str[i] != '\0') {
        myprint_char(str[i]);
        i++;
    }
}

