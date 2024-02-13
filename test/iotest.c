/* iotest.c */

#include <stdlib.h>
#include <io.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>

int main ()
{
  char buf[256], *p;
  int f, n;
  char *txt = "iotest!\r\n";

  prts ("Output file name=");
  read (1, buf, sizeof (buf));
  p = strchr (buf, '\r');
  if (p != NULL) *p = 0;
  p = strchr (buf, '\n');
  if (p != NULL) *p = 0;
  f = open (buf, O_WRONLY|O_CREAT|O_TRUNC|O_EXCL, S_IREAD|S_IWRITE);
  if (f < 0)
    {
      if (errno == EEXIST)
        prts ("File already exists\r\n");
      else
        {
          prts ("open failed, errno=");
          prti (errno);
          prts ("\r\n");
        }
      return (1);
    }
  n = write (f, txt, strlen (txt));
  if (n != strlen (txt))
    {
      prts ("write failed, errno=");
      prti (errno);
      prts ("\r\n");
      return (1);
    }
  if (close (f) != 0)
    {
      prts ("close failed, errno=");
      prti (errno);
      prts ("\r\n");
    }
  return (0);
}
