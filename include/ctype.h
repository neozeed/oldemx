/* ctype.h (emx/gcc) */

#if !defined (__CTYPE_H)
#define __CTYPE_H

#if !defined (__CTYPE_C)
extern unsigned char _ctype[];
#endif

#define _UPPER  0x01
#define _LOWER  0x02
#define _DIGIT  0x04
#define _XDIGIT 0x08
#define _CNTRL  0x10
#define _SPACE  0x20
#define _PUNCT  0x40
#define _PRINT  0x80

#define isalnum(c)  ((_ctype+1)[c] & (_UPPER|_LOWER|_DIGIT))
#define isalpha(c)  ((_ctype+1)[c] & (_UPPER|_LOWER))
#define iscntrl(c)  ((_ctype+1)[c] & (_CNTRL))
#define isdigit(c)  ((_ctype+1)[c] & (_DIGIT))
#define isgraph(c)  ((_ctype+1)[c] & (_PUNCT|_UPPER|_LOWER|_DIGIT))
#define islower(c)  ((_ctype+1)[c] & (_LOWER))
#define isprint(c)  ((_ctype+1)[c] & (_PRINT))
#define ispunct(c)  ((_ctype+1)[c] & (_PUNCT))
#define isspace(c)  ((_ctype+1)[c] & (_SPACE))
#define isupper(c)  ((_ctype+1)[c] & (_UPPER))
#define isxdigit(c) ((_ctype+1)[c] & (_XDIGIT))

#define isascii(c) ((unsigned)(c) <= 0x7f)
#define toascii(c) ((c) & 0x7f)

#if !defined (__CTYPE_C)
static __inline__ int _toupper (int c) { return (c-'a'+'A'); }
static __inline__ int _tolower (int c) { return (c-'A'+'a'); }
static __inline__ int toupper(int c) {return (islower(c) ? _toupper(c) : c);}
static __inline__ int tolower(int c) {return (isupper(c) ? _tolower(c) : c);}
#endif

#endif
