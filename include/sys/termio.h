/* sys/termio.h (emx/gcc) */

#if !defined (__TERMIO_H)

#define __TERMIO_H

/* request codes */

#define TCGETA      1
#define TCSETA      2
#define TCSETAW     3
#define TCSETAF     4

/* c_cc indexes */

#define VINTR       0
#define VQUIT       1
#define VERASE      2
#define VKILL       3
#define VEOF        4
#define VEOL        5
#define VMIN        6
#define VTIME       7

#define NCC         8   /* Number of the above */

/* c_iflag, emx ignores most of the following bits */

#define IGNBRK      0x0001
#define BRKINT      0x0002
#define IGNPAR      0x0004
#define PARMRK      0x0008
#define INPCK       0x0010
#define ISTRIP      0x0020
#define INLCR       0x0040
#define IGNCR       0x0080
#define ICRNL       0x0100
#define IUCLC       0x0200
#define IXON        0x0400
#define IXANY       0x0800
#define IXOFF       0x1000
#define IDEFAULT    0x8000

/* c_oflag, emx ignores all of the following bits */

#define OPOST       0x0001
#define OLCUC       0x0002
#define ONLCR       0x0004
#define OCRNL       0x0008
#define ONOCR       0x0010
#define ONLRET      0x0020
#define OFILL       0x0040
#define OFDEL       0x0080
#define NLDLY       0x0100 /* mask */
#define NL0         0x0000
#define NL1         0x0100
#define CRDLY       0x0600 /* mask */
#define CR0         0x0000
#define CR1         0x0200
#define CR2         0x0400
#define CR3         0x0600
#define TABDLY      0x1800 /* mask */
#define TAB0        0x0000
#define TAB1        0x0800
#define TAB2        0x1000
#define TAB3        0x1800
#define BSDLY       0x2000 /* mask */
#define BS0         0x0000
#define BS1         0x2000
#define VTDLY       0x4000 /* mask */
#define VT0         0x0000
#define VT1         0x4000
#define FFDLY       0x8000 /* mask */
#define FF0         0x0000
#define FF1         0x8000

/* c_cflag, emx ignores all of the following bits */

#define CBAUD       0x000f /* mask */
#define B0          0x0000
#define B50         0x0001
#define B75         0x0002
#define B110        0x0003
#define B134        0x0004
#define B150        0x0005
#define B200        0x0006
#define B300        0x0007
#define B600        0x0008
#define B1200       0x0009
#define B1800       0x000a
#define B2400       0x000b
#define B4800       0x000c
#define B9600       0x000d
#define B19200      0x000e
#define B38400      0x000f
#define CSIZE       0x0030 /* mask */
#define CS5         0x0000
#define CS6         0x0010
#define CS7         0x0020
#define CS8         0x0030
#define CSTOPB      0x0040
#define CREAD       0x0080
#define PARENB      0x0100
#define PARODD      0x0200
#define HUPCL       0x0400
#define CLOCAL      0x0800
#define LOBLK       0x1000

/* c_lflag, emx ignores some of the following bits */

#define ISIG        0x0001
#define ICANON      0x0002
#define XCASE       0x0004
#define ECHO        0x0008
#define ECHOE       0x0010
#define ECHOK       0x0020
#define ECHONL      0x0040
#define NOFLSH      0x0080


struct termio
    {
    unsigned int  c_iflag;
    unsigned int  c_oflag;
    unsigned int  c_cflag;
    unsigned int  c_lflag;
    unsigned int  c_line;
    unsigned char c_cc[NCC];
    };

#endif
