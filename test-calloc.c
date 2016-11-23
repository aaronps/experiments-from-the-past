#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char **argv)
{
	char *p;
	int i=256;
	int n=2;

	printf("--I'll calloc(%d,%d)\n", n,i);
	p=(char *)calloc(n,i);

	printf("--returned %08x\n",p);
	free(p);

	return(0);
}

