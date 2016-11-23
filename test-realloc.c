#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char **argv)
{
	char *p,*p2;
	int i=256;
	int i2=500;

	printf("--I'll malloc %d\n", i);
	p=(char *)malloc(i);
	printf("--returned %08x\n",p);
	
	printf("--I'll realloc(%08x,%d)\n",p,i2);
	
	p2=realloc(p,i2);
	printf("--returned %08x\n",p2);
	free(p);

	return(0);
}

