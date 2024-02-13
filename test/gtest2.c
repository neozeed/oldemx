/* gtest2.c */

#include <io.h>

static int i;

int main ()
{
  char *p, buf[100];

  p = "test!\n";
  for (i=0; i<10; ++i)
      write (1, p, strlen(p));
  for (;;)
    {
      i = read (0, buf, sizeof (buf));
      if (i == -1 || i == 0)
        break;
      write (1, buf, i);
    }
return (0);
}
