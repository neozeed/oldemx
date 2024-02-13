//
//
//

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int c;

	printf("Press '.' to quit.\n");
	while ((c = _read_kbd(0, 1, 0)) != '.')
	{
		if (c == 0)
			c = - _read_kbd(0, 1, 0);
		printf("%d: [", c);
		if (c < ' ')
		{
			printf("^");
			c += '@';
		}
		printf("%c]\n", c);
	}
	return 0;
}

