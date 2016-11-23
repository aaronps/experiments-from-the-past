#include "nchino.h"

int main(int argc, char *argv[])
{
	FILE *origen=NULL;

	FILE *fuente1;
	FILE *fuente2;

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

	if (argc<2) {
		fprintf(stderr,"ERROR: falta el nombre del archivo a ver\n");
		return(ERRPARAM);
	}	

	if ((origen=fopen(argv[1],"r"))==NULL) {
		fprintf(stderr,"File not found\n");
		return(FILENOTFOUND);
	}


    fuente1=fopen("cclib.16","rb");
    fuente2=fopen("cclib.16a","rb");

while (!salida)
{
	if ((caracter=lee_caracter(origen))==ERREOF) {
		fprintf(stderr,"--End Of File--\n");
		return(0);
	}

  
    printf("%x\n",caracter);
    if (caracter>=0xa1a1 && caracter<=0xa7fe)
    {
        caracter-=(((caracter/0x100)&0xff)-0xa1)*0xa2;
        caracter-=0xa1a1;

        fseek(fuente1,caracter*LONGCHAR,SEEK_SET);
        fread(fuente,32,1,fuente1);
    }
    if (caracter>=0xa8a1 && caracter<=0xa9fe)
    {
        caracter-=(((caracter/0x100)&0xff)-0xa8)*0xa2;
        caracter-=0xa8a1;

        fseek(fuente2,caracter*LONGCHAR,SEEK_SET);
        fread(fuente,32,1,fuente2);
    }
    if (caracter>=0xb0a1 && caracter<=0xf7fe)
    {
        caracter-=(((caracter/0x100)&0xff)-0xb0)*0xa2;
        caracter-=0xb0a1;
        fseek(fuente1,(caracter*LONGCHAR)+21056,SEEK_SET);
        fread(fuente,32,1,fuente1);
    }
   else { printf("Caracter no encontrado"); return 1; }

/*    fseek(fuente1,21056+(caracter*32),SEEK_SET);
    fread(fuente,32,1,fuente1);
  */
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
        printf("\n");
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


    fclose(origen);
    fclose(fuente1);
    fclose(fuente2);
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

