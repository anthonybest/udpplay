#include <stdio.h>
int main(int argc, char * argv[])
{
	int c = 0;
	char x;
	if(argc != 2)
	{
		fprintf(stderr, " Usage: %s count\n", argv[0]);
		exit(1);
	}
	c = atoi(argv[1]);

	while(c > 0)
	{
		x = (c--%0x5f)+0x20;
		fwrite(&x, sizeof(char), 1, stdout);
	}


	return 0;
}

