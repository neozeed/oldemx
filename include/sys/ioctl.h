/* ioctl.h (emx/gcc) */

#if !defined (_SYS_IOCTL_H)
#define _SYS_IOCTL_H

#if !defined (TCGETA)
#define TCGETA      1
#define TCSETA      2
#define TCSETAW     3
#define TCSETAF     4
#define TCFLSH      5
#endif

#if !defined (FIONREAD)
#define FIONREAD   16
#endif

#if !defined (FGETHTYPE)
#define FGETHTYPE  32
#endif

#if !defined (HT_FILE)
#define HT_FILE         0
#define HT_UPIPE        1
#define HT_NPIPE        2
#define HT_DEV_OTHER    3
#define HT_DEV_NUL      4
#define HT_DEV_KBD      5
#define HT_DEV_VIO      6
#define HT_DEV_CLK      7
#define HT_ISDEV(n)     ((n) >= HT_DEV_OTHER && (n) <= HT_DEV_CLK)
#endif

int ioctl (int handle, int request, ...);

#endif /* !defined (_SYS_IOCTL_H) */
