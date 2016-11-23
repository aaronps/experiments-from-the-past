#include <stdio.h>

#define TEXTX 16
#define TEXTY 16
#define LONGCHAR 32
#define CAR 0

int main(void)
{
    FILE *texto;
    FILE *fuente1;
    FILE *fuente2;
    int contadorfilas, contadorcolumnas;
    int salida, cuantos;
    unsigned char nombre[256];
    unsigned char que;
    unsigned int caracter;
    unsigned int ctemp;
    unsigned int carmask;
    unsigned int mascara;
    unsigned char fuente[32];
    char frase[200];

    salida=0;
    que=0;

    printf("file name: ");
    scanf("%s",nombre);

    texto=fopen(nombre, "rb");
    if (texto==NULL) salida=1;
    fuente1=fopen("cclib.16","rb");
    fuente2=fopen("cclib.16a","rb");

    scanf("%c",&que);

while (!salida)
{
    cuantos=0;
    cuantos=fread(frase,2,1,texto);
    if (cuantos==NULL)
    {
        printf("END OF FILE-----------------------\n");
        salida=1;
        frase[0]=0;
        frase[1]=0;
    }
    caracter=((frase[CAR]&0xff)<<8)|((frase[CAR+1]&0xff));
    caracter=caracter&0xffff;


/*    scanf("%04x",&caracter); */
/*     caracter=0xa3b0; */
  
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
   /* else { printf("Caracter no encontrado"); return 1; } */

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


    fclose(texto);
    fclose(fuente1);
    fclose(fuente2);
    return 0;
}
