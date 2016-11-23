extern "C" {
  #include <stdio.h>
}

int
main(int argc, char **argv)
{
	char *p;
	int i=500;

	printf("--I'll new %d\n", i);
	p=new char[i];

	printf("--returned %08x\n",p);
	delete(p);

	return(0);

}
