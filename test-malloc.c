#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char **argv)
{
	char *p;
	int i=500;

	printf("--I'll malloc %d\n", i);
	p=(char *)malloc(i);

	printf("--returned %08x\n",p);
	free(p);

	return(0);
}

