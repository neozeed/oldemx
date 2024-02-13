/* varargs.h (emx/gcc) */

#define __VA_SIZE(type)   (4 * ((sizeof (type) + 3) / 4))

#define va_alist __builtin_va_alist
#define va_dcl int __builtin_va_alist;
#define va_list char *

#define va_start(alist) alist = (char *)&__builtin_va_alist
#define va_end(alist)
#define va_arg(alist,type) (alist += __VA_SIZE (type), \
                            *((type *)(alist - __VA_SIZE (type))))
