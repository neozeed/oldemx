/* stdio.h (emx/gcc) */

#if !defined (_SIZE_T)
#define _SIZE_T
typedef unsigned int size_t;
#endif

#if !defined (NULL)
#define NULL ((void *)0)
#endif

#if !defined (BUFSIZ)
#define BUFSIZ 5120
#endif

#if !defined (_FILE_DEFINED)

#define _FILE_DEFINED

struct _stdio
    {
    char *ptr;
    char *buffer;
    int rcount;
    int wcount;
    int handle;
    int flags;
    int buf_size;
    int tmpidx;
    char char_buf;
    char reserved1[3];
    };

typedef struct _stdio FILE;

extern struct _stdio _streams[];

#define stdin  (&_streams[0])
#define stdout (&_streams[1])
#define stderr (&_streams[2])

#endif

#if !defined (SEEK_SET)
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2
#endif

#if !defined (EOF)
#define EOF (-1)
#endif

#if !defined (_IOREAD)
#define _IOREAD 0x01
#define _IOWRT  0x02
#define _IORW   0x04
#define _IOEOF  0x20
#define _IOERR  0x40
#define _IOFBF  0x0000
#define _IOLBF  0x1000
#define _IONBF  0x2000
#endif

#if !defined (P_tmpdir)
#define P_tmpdir "/"
#define L_tmpnam (sizeof (P_tmpdir) + 13)
#endif

#if !defined (_FPOS_T_DEFINED)
#define _FPOS_T_DEFINED
typedef long fpos_t;
#endif

#if !defined (_VA_LIST_DEFINED)
#define _VA_LIST_DEFINED
typedef char *va_list;
#endif

void clearerr (FILE *stream);
int fclose (FILE *stream);
int fcloseall (void);
FILE *fdopen (int handle, const char *mode);
int fflush (FILE *stream);
int fgetc (FILE *stream);
int fgetchar (void);
int fgetpos (FILE *stream, fpos_t *pos);
char *fgets (char *buffer, int n, FILE *stream);
int flushall (void);
FILE *fopen (const char *fname, const char *mode);
int fprintf (FILE *stream, const char *format, ...);
int fputc (int c, FILE *stream);
int fputchar (int c);
int fputs (const char *string, FILE *stream);
size_t fread (void *buffer, size_t size, size_t count, FILE *stream);
FILE *freopen (const char *fname, const char *mode, FILE *stream);
int fscanf (FILE *stream, const char *format, ...);
int fseek (FILE *stream, long offset, int origin);
int fsetpos (FILE *stream, const fpos_t *pos);
long ftell (FILE *stream);
size_t fwrite (const void *buffer, size_t size, size_t count, FILE *stream);
char *gets (char *buffer);
void perror (const char *string);
int printf (const char *format, ...);
int puts (const char *string);
int remove (const char *name);
int rename (const char *old_name, const char *new_name);
void rewind (FILE *stream);
int rmtmp (void);
int scanf (const char *format, ...);
void setbuf (FILE *stream, char *buffer);
int setbuffer (FILE *stream, char *buffer, size_t size);
int setvbuf (FILE *stream, char *buffer, int mode, size_t size);
int sprintf (char *buffer, const char *format, ...);
int sscanf (const char *buffer, const char *format, ...);
char *tempnam (const char *dir, const char *prefix);
FILE *tmpfile (void);
char *tmpnam (char *string);
int ungetc (int c, FILE *stream);
int unlink (const char *name);
int vfprintf (FILE *stream, const char *format, va_list arg_ptr);
int vprintf (const char *format, va_list arg_ptr);
int vsprintf (char *buffer, const char *format, va_list arg_ptr);

int _fill (FILE *stream);
int _flush (int c, FILE *stream);

int _fseek_hdr (FILE *stream);

#if !defined (_STDIO_H)
#define _STDIO_H
static int __inline__ fileno (FILE *s) { return (s->handle); }
static int __inline__ feof (FILE *s) { return (s->flags & _IOEOF ? 1 : 0); }
static int __inline__ ferror (FILE *s) { return (s->flags & _IOERR ? 1 : 0); }
static int __inline__ getc (FILE *s)
    { return (--s->rcount >= 0 ? (unsigned char)*s->ptr++
                               : _fill (s)); }
static int __inline__ putc (int c, FILE *s)
    { return (--s->wcount >= 0 && (c != '\n' || !(s->flags & _IOLBF))
                               ? (unsigned char)(*s->ptr++ = (char)c)
                               : _flush (c, s)); }
static int __inline__ getchar (void) { return (getc (stdin)); }
static int __inline__ putchar (int c) { return (putc (c, stdout)); }
#endif
