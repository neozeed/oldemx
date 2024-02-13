/* assert.h (emx/gcc) */

#undef assert

#if defined (NDEBUG)
#define assert(exp) ((void)0)
#else
void _assert (char *string, char *fname, unsigned int line);
#define assert(exp) ((exp) ? (void)0 : _assert (#exp, __FILE__, __LINE__))
#endif
