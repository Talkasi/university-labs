#include "my_snprintf.h"
#include <stdarg.h>
#include <stdio.h>

enum format_flags
{
    ZERO_PADDING = 1,
    LEFT_ADJUSTED = 2,
    SIGN_ALWAYS = 4,
    SIGN_BLANK = 8,
    PRECISION_GIVEN = 16
};

typedef struct
{
    char *str;
    size_t max_size;
    size_t n_printed;
} buf_t;

typedef struct
{
    int min_width;
    int precision;
    int flags;
} format_t;

int my_snprintf(char *str, size_t size, const char *format, ...)
{
    int r;
    va_list args;
    va_start(args, format);
    r = my_vsnprintf(str, size, format, args);
    va_end(args);
    return r;
}

static void print_padding(buf_t *buf, char c, int n)
{
    while (n-- > 0)
    {
        if (buf->max_size > buf->n_printed + 1)
            buf->str[buf->n_printed] = c;

        ++buf->n_printed;
    }
}

static char get_sign_char(format_t f, int num)
{
    if (num < 0)
        return '-';

    if (f.flags & SIGN_ALWAYS)
        return '+';

    if (f.flags & SIGN_BLANK)
        return ' ';

    return '\0';
}

static void print_d_formatted(buf_t *buf, format_t f, int num, char *num_buf, int num_buf_len)
{
    char sign_c = get_sign_char(f, num);

    int w = num_buf_len;
    if (f.flags & LEFT_ADJUSTED)
    {
        int num_width = w;
        if (f.precision == 0 && num == 0)
            num_width = 0;
        if (num_width < f.precision)
            num_width = f.precision;
        if (sign_c != '\0')
            ++num_width;

        if (sign_c != '\0')
            print_padding(buf, sign_c, 1);

        if (!((f.flags & PRECISION_GIVEN) && f.precision == 0 && num == 0))
        {
            if (w < f.precision)
                print_padding(buf, '0', f.precision - w);

            for (int i = num_buf_len - 1; i >= 0; --i)
                print_padding(buf, num_buf[i], 1);
        }

        if (num_width < f.min_width)
            print_padding(buf, ' ', f.min_width - num_width);
    }
    else
    {
        int num_width = w;
        if (f.precision == 0 && num == 0)
            num_width = 0;
        if (num_width < f.precision)
            num_width = f.precision;
        if (!(f.flags & PRECISION_GIVEN) && (f.flags & ZERO_PADDING) && num_width < f.min_width)
            num_width = f.min_width;
        else if (sign_c)
            ++num_width;

        if (num_width < f.min_width)
            print_padding(buf, ' ', f.min_width - num_width);

        if (sign_c)
        {
            print_padding(buf, sign_c, 1);
            --num_width;
        }

        if (w < num_width)
            print_padding(buf, '0', num_width - w);

        if (!((f.flags & PRECISION_GIVEN) && f.precision == 0 && num == 0))
            for (int i = num_buf_len - 1; i >= 0; --i)
                print_padding(buf, num_buf[i], 1);
    }
}

#define MAX_DEC_BUF_LEN 32
static int print_d_reverce(char *num_buf, int num_buf_size, int num)
{
    if (num_buf_size <= 0)
        return 0;

    if (num == 0)
    {
        num_buf[0] = '0';
        return 1;
    }

    int i = 0;
    int sign = num > 0 ? 1 : -1;
    while (num && i < num_buf_size)
    {
        num_buf[i++] = '0' + sign * (num % 10);
        num /= 10;
    }

    return i;
}

static void print_d(buf_t *buf, format_t f, int num)
{
    char tmp_num_buf[MAX_DEC_BUF_LEN];
    int num_len = print_d_reverce(tmp_num_buf, sizeof(tmp_num_buf), num);
    print_d_formatted(buf, f, num, tmp_num_buf, num_len);
}

static void print_c(buf_t *buf, format_t f, char c)
{
    if (f.min_width > 1 && !(f.flags & LEFT_ADJUSTED))
        print_padding(buf, ' ', f.min_width - 1);

    print_padding(buf, c, 1);

    if (f.min_width > 1 && (f.flags & LEFT_ADJUSTED))
        print_padding(buf, ' ', f.min_width - 1);
}

static void copy_all_before_conversion(const char **format, buf_t *buf)
{
    while (**format != '\0' && **format != '%')
    {
        if (buf->max_size > buf->n_printed + 1)
            buf->str[buf->n_printed] = **format;

        ++*format;
        ++buf->n_printed;
    }
}

static void init_format_flags(const char **format, format_t *f)
{
    f->flags = 0;

    while (**format == '0' || **format == '-' || **format == '+' || **format == ' ')
    {
        if (**format == '0')
            f->flags |= ZERO_PADDING;
        else if (**format == '-')
            f->flags |= LEFT_ADJUSTED;
        else if (**format == '+')
            f->flags |= SIGN_ALWAYS;
        else if (**format == ' ')
            f->flags |= SIGN_BLANK;
        else
            break;

        ++*format;
    }
}

static void init_min_width(const char **format, format_t *f, va_list arg)
{
    if (**format == '*')
    {
        ++*format;
        f->min_width = va_arg(arg, int);
        if (f->min_width < 0)
        {
            f->flags |= LEFT_ADJUSTED;
            f->min_width = -f->min_width;
        }
        return;
    }

    while ('0' <= **format && **format <= '9')
    {
        f->min_width = f->min_width * 10 + **format - '0';
        ++*format;
    }
}

static void init_precision(const char **format, format_t *f, va_list arg)
{
    if (**format == '.')
    {
        ++*format;
        f->precision = 0;
        f->flags |= PRECISION_GIVEN;
        if (**format == '*')
        {
            ++*format;
            f->precision = va_arg(arg, int);
            if (f->precision < 0)
                f->precision = 0;

            return;
        }

        while ('0' <= **format && **format <= '9')
        {
            f->precision = f->precision * 10 + **format - '0';
            ++*format;
        }
    }
}

int my_vsnprintf(char *str, size_t size, const char *format, va_list arg)
{
    buf_t buf = { .str = str, .max_size = size, .n_printed = 0 };
    format_t f = { .min_width = 0, .precision = 0, .flags = 0 };

    while (*format)
    {
        copy_all_before_conversion(&format, &buf);
        if (*format == '\0')
            break;

        ++format;
        init_format_flags(&format, &f);
        init_min_width(&format, &f, arg);
        init_precision(&format, &f, arg);

        if (*format == 'd')
            print_d(&buf, f, va_arg(arg, int));
        else if (*format == 'c')
            print_c(&buf, f, va_arg(arg, int));
        else if (*format == '\0')
            break;

        ++format;
    }

    if (buf.max_size >= buf.n_printed + 1)
        buf.str[buf.n_printed] = '\0';
    else if (buf.max_size != 0)
        buf.str[buf.max_size - 1] = '\0';

    return buf.n_printed;
}
