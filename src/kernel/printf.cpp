#include "printf.hpp"
#include "common.hpp"

namespace kernel {

static void print_char(char c) {
    char s[2] = {c, 0};
    print(s);
}

static void print_num(long long val, int base, bool sign) {
    char buf[32];
    int n = 0;
    unsigned long long uval = sign && val < 0 ? -val : val;
    if (val == 0) buf[n++] = '0';
    while (uval) {
        int d = uval % base;
        buf[n++] = d < 10 ? '0' + d : 'a' + d - 10;
        uval /= base;
    }
    if (sign && val < 0) buf[n++] = '-';
    for (int i = n - 1; i >= 0; --i) print_char(buf[i]);
}

void printf(const char* fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    for (const char* p = fmt; *p; ++p) {
        if (*p != '%') {
            print_char(*p);
            continue;
        }
        ++p;
        // 检查长度修饰符
        bool long_flag = false, longlong_flag = false;
        if (*p == 'l') {
            ++p;
            if (*p == 'l') {
                ++p;
                longlong_flag = true;
            } else {
                long_flag = true;
            }
        }
        switch (*p) {
        case 'd': case 'i':
            if (longlong_flag)
                print_num(va_arg(ap, long long), 10, true);
            else if (long_flag)
                print_num(va_arg(ap, long), 10, true);
            else
                print_num(va_arg(ap, int), 10, true);
            break;
        case 'u':
            if (longlong_flag)
                print_num(va_arg(ap, unsigned long long), 10, false);
            else if (long_flag)
                print_num(va_arg(ap, unsigned long), 10, false);
            else
                print_num(va_arg(ap, unsigned int), 10, false);
            break;
        case 'x': case 'X':
            if (longlong_flag)
                print_num(va_arg(ap, unsigned long long), 16, false);
            else if (long_flag)
                print_num(va_arg(ap, unsigned long), 16, false);
            else
                print_num(va_arg(ap, unsigned int), 16, false);
            break;
        case 'c':
            print_char((char)va_arg(ap, int));
            break;
        case 's': {
            const char* s = va_arg(ap, const char*);
            print(s ? s : "(null)");
            break;
        }
        case '%':
            print_char('%');
            break;
        default:
            print_char('%');
            print_char(*p);
            break;
        }
    }
    va_end(ap);
}

} // namespace kernel 