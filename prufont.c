#include "nchino.h"

int main(int argc, char *argv[])
{
	FILE *fuente1;

    int contadorfilas, contadorcolumnas;
    int salida=0,cuantos;
    unsigned char nombre[256];
    unsigned char que;
    unsigned int caracter;
    unsigned int ctemp;
    unsigned int carmask;
    unsigned int mascara;
    unsigned char fuente[32];
    char frase[200];
	que=0;

    fuente1=fopen("cclib.16","rb");

while (!salida)
{

  
	if (fread(fuente,32,1,fuente1)<1) return (0);

if (!salida)
    for (contadorfilas=0;contadorfilas<TEXTY;contadorfilas++)
    {
        carmask=((fuente[contadorfilas*2]&0xff)<<8)+((fuente[(contadorfilas*2)+1]&0xff));
        carmask=carmask&0xffff;
        mascara=0x8000;
        for (contadorcolumnas=0;contadorcolumnas<TEXTX;contadorcolumnas++)
        {
            if (carmask&mascara) printf("*");
            else printf(" ");
            mascara=mascara>>1;
        }
        printf("%d\n",contadorfilas);
    }

    scanf("%c",&que);
    switch (que)
    {
    case 'q':
    case 'Q': salida=1; break;
    case 13:
        break;
    default:
        break;

    } 

} /* while */


    fclose(fuente1);
    return 0;
}

int lee_caracter(FILE *f)
{
	int c=0,tmp=0;
	if ((fread(&tmp,1,1,f))<1) return(ERREOF);
	if (tmp>=0xa1) { 
		c=tmp<<8;
		tmp=0;
		if ((fread(&tmp,1,1,f))<1) return(ERREOF);
		c|=tmp;
	}
	return(c);
}

