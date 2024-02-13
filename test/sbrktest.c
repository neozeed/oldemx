/* sbrktest.c */

#include <stdlib.h>
#include <string.h>
#include <io.h>

int main ()
{
  char buf[256], *p;
  int i, n, f;

  f = 0;
  for (;;)
    {
      n = (int)sbrk (0);
      prts ("sbrk = "); prti (n); prtc ('\n');
      n = (int)ulimit (3, 0);
      prts ("ulimit (3, 0) = "); prti (n); prtc ('\n');
      prts ("? ");
      read (1, buf, sizeof (buf));
      p = strchr (buf, '\n');
      if (p != NULL) *p = 0;
      if (buf[0] == 'q')
        return (0);
      if (buf[0] == 'f')
        {
          f = !f;
          prts ("fill = ");
          prts ((f ? "on" : "off"));
          prtc ('\n');
          continue;
        }
      i = atoi (buf);
      p = sbrk (i);
      if ((int)p == -1)
        prts ("error\n");
      else
        {
          prts ("ok.\n");
          if (i > 0 && f)
            memset (p, '*', i);
        }
    }
}
