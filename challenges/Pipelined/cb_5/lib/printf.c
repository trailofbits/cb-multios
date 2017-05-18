#include "libcgc.h"
#include "cgc_cgc_libc.h"
#include "cgc_cgc_types.h"
#include "cgc_printf.h"

cgc_size_t cgc_transmit_char(int fd, char d);
cgc_size_t cgc_transmit_unsigned(int fd, unsigned int value);
cgc_size_t cgc_transmit_string(int fd, char *string);

cgc_size_t cgc_printf(int fd, const char *format, ...) {
    va_list ap;
    cgc_size_t count = 0;

    va_start(ap, format);
    for (count = 0; *format != '\0'; ++format) {
        if (*format == '%') {
            switch (*++format) {
                case 'c':
                    count += cgc_transmit_char(fd, va_arg(ap, int));
                    break;

                case 's':
                    count += cgc_transmit_string(fd, va_arg(ap, char *));
                    break;

                case 'u':
                    count += cgc_transmit_unsigned(fd, va_arg(ap, unsigned));
                    break;

                default:
                    count += cgc_transmit_char(fd, *format);
                    break;
            }
        } else {
            count += cgc_transmit_char(fd, *format);
        }
    }
    va_end(ap);
    return count;
}

cgc_size_t cgc_transmit_char(int fd, char d) {
    cgc_size_t sent;
    int ret;
    ret = cgc_transmit(fd, &d, 1, &sent);
    if (ret != 0) {
        return 0;
    }
    return sent;
}

cgc_size_t cgc_transmit_string(int fd, char *string) {
    cgc_size_t count;
    int ret;

    count = cgc_strlen(string);

    ret = cgc_transmit_all(fd, string, count);
    if (ret != 0) {
        return 0;
    }

    return count;
}

cgc_size_t cgc_transmit_unsigned(int fd, unsigned int value) {
    cgc_size_t count;
    unsigned int digit, tenth;

    tenth = value / 10;
    digit = value - 10 * tenth + '0';
    count = tenth != 0 ? cgc_transmit_unsigned(fd, tenth) : 0;

    cgc_transmit_char(fd, digit);
    return count;
}
