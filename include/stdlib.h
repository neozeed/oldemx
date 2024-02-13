/* stdlib.h (emx/gcc) */

#if !defined (_SIZE_T)
#define _SIZE_T
typedef unsigned int size_t;
#endif

#if !defined (NULL)
#define NULL ((void *)0)
#endif

#if !defined (_DIV_T_DEFINED)
#define _DIV_T_DEFINED
typedef struct _div_t
    {
    int quot;
    int rem;
    } div_t;
typedef struct _ldiv_t
    {
    long quot;
    long rem;
    } ldiv_t;
#endif

#if !defined (RAND_MAX)
#define RAND_MAX 0x7fff
#endif

#if !defined (min)
#define min(a,b) (((a) < (b)) ? (a) : (b))
#define max(a,b) (((a) > (b)) ? (a) : (b))
#endif

#if !defined (_HEAPOK)
#define _HEAPOK       0
#define _HEAPEMPTY    1
#define _HEAPBADBEGIN 2
#define _HEAPBADNODE  3
#define _HEAPBADEND   4
#define _HEAPBADROVER 5
#endif

#if !defined (EXIT_SUCCESS)
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#endif

extern int errno;

extern char **environ;

extern const char *sys_errlist[];
extern const int sys_nerr;

extern const unsigned int _emx_vcmp;
extern const unsigned int _emx_env;
extern const unsigned char _osminor;
extern const unsigned char _osmajor;
extern const char _emx_vprt[5];

void abort (void);
unsigned alarm (unsigned sec);
int atexit (void (*func)(void));
int atoi (const char *string);
long atol (const char *string);
double atof (const char *string);
void *bsearch (const void *key, const void *base, size_t num, size_t width,
               int (*compare)(const void *key, const void *element));
void *calloc (size_t elements, size_t size);
int chdir (const char *name);
div_t div (int num, int den);
void volatile exit (int ret);
void free (void *mem);
char *getcwd (char *buffer, int size);
char *getenv (const char *name);
int getpagesize (void);
char *itoa (int value, char *string, int radix);
ldiv_t ldiv (long num, long den);
char *ltoa (long value, char *string, int radix);
void *malloc (size_t size);
int mkdir (const char *name);
void perror (const char *string);
int putenv (const char *string);
void qsort (void *base, size_t num, size_t width,
            int (*compare)(const void *x1, const void *x2));
int rand (void);
void *realloc (void *mem, size_t size);
void *sbrk (int incr);
int rmdir (const char *name);
unsigned sleep (unsigned sec);
void srand (unsigned int seed);
long strtol (const char *string, char **end_ptr, int radix);
unsigned long strtoul (const char *string, char **end_ptr, int radix);
double strtod (const char *string, char **end_ptr);
int system (const char *command);
long ulimit (int cmd, long newlimit);
char *ultoa (unsigned long value, char *string, int radix);

int _core (int handle);
void _defext (char *dst, const char *ext);
void volatile _exit (int ret);
void *_expand (void *mem, size_t new_size);
int _heapchk (void);
int _heapset (unsigned fill);
size_t _msize (const void *mem);
int _path (char *dst, const char *name);
int _read_kbd (int echo, int wait, int sig);
void _response (int *argcp, char ***argvp);
void _searchenv (const char *file, const char *var, char *path);
void _wildcard (int *argcp, char ***argvp);

#if !defined (__ABS)                                     /* see also math.h */
#define __ABS
static __inline__ int abs (int n) { return (n < 0 ? -n : n); }
static __inline__ long labs (long n) { return (n < 0 ? -n : n); }
#endif
