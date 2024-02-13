/* gtest3.c */

#include <stdlib.h>

int main ()
{
  int i;

  prts ("gtest3.c:\r\n");
  for (i = 0; i < 10; ++i)
    {
      prti (i); prtc (' ');
    }
prts ("\r\n");
return (0);
}
