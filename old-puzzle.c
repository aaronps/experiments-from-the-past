#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "SDL.h"
//#include "SDL_image.h"

typedef struct {
	int x;
	int y;
} point;


int make_blocks(int,int);
void free_blocks(void);
int draw_block(int,int,int);
int make_puzzle(void);
int draw_puzzle(void);
void swap_blocks(int,int);
void mark_selected(int);

SDL_Surface *window;
SDL_Surface *image;
SDL_Rect *iblock;
int nblocks;
int puzzle_xlen, puzzle_ylen;
int puzzle_bxlen, puzzle_bylen;
int *puzzle;
int marked;
point mark;

int
main (int argc, char **argv)
{
	SDL_Rect r;
	SDL_Event e;
	int n,m,c,x,y,fromb,tob;
	SDL_Surface *tsurf;
	
	marked=0;
	
	if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
		printf("ERROR: Cant initialize SDL\n");
		return(1);
	}
	
	atexit(SDL_Quit);
	
	window = SDL_SetVideoMode(640,480,16,SDL_SWSURFACE);
	if ( window == NULL ) {
		printf("ERROR: Can't create the window\n");
		return(1);
	}

	tsurf=SDL_CreateRGBSurface(SDL_SWSURFACE,1,1,32,0xff0000,
			0xff00,0xff,0xff000000);
	printf("palette=%08x\nBitsPerPixel=%d\nBytesPerPixel=%d\nRmask=%08x,Gmask=%08x,Bmask=%08x,Amask=%08x\nRshift=%d,Gshift=%d,Bshift=%d,Ashift=%d\nRloss=%d,Gloss=%d,Bloss=%d,Aloss=%d\ncolorkey=%08x\nalpha=%x\n",
			tsurf->format->palette,
			tsurf->format->BitsPerPixel,
			tsurf->format->BytesPerPixel,
			tsurf->format->Rmask,
			tsurf->format->Gmask,
			tsurf->format->Bmask,
			tsurf->format->Amask,
			tsurf->format->Rshift,
			tsurf->format->Gshift,
			tsurf->format->Bshift,
			tsurf->format->Ashift,
			tsurf->format->Rloss,
			tsurf->format->Gloss,
			tsurf->format->Bloss,
			tsurf->format->Aloss,
			tsurf->format->colorkey,
			tsurf->format->alpha);
	
	image = SDL_LoadBMP("prueba.bmp");
	if ( image == NULL ) {
		printf("ERROR: Can't load image\n");
		return(2);
	}
	
	make_blocks(5,5);

	make_puzzle();

	draw_puzzle();


	while (1) {
		SDL_WaitEvent(&e);
		switch(e.type) {
			case SDL_MOUSEBUTTONDOWN:
				//e.button.button;e.button.x;e.button.y
				x=e.button.x/puzzle_bxlen;
				y=e.button.y/puzzle_bylen;
				if ( !marked ) {
					fromb=(y*puzzle_xlen)+x;
					marked=1;
					mark_selected(fromb);
					draw_puzzle();
				} else {
					tob=(y*puzzle_xlen)+x;
					marked=0;
					swap_blocks(fromb,tob);
					draw_puzzle();
				}
				
				break;
			case SDL_KEYDOWN:
			case SDL_QUIT:
			exit(0);
		}
	}
	return(0);
}

int
make_blocks(int nx, int ny)
{
	int c,n,m;

	puzzle_xlen=nx;
	puzzle_ylen=ny;
	
	nblocks=puzzle_xlen * puzzle_ylen;

	iblock=(SDL_Rect *)calloc(nblocks, sizeof(SDL_Rect));
	if ( !iblock ) {
		printf("ERROR: Not enought memory for blocks\n");
		exit(1);
	}

	puzzle_bxlen=640/puzzle_xlen;
	puzzle_bylen=480/puzzle_ylen;

	c=0;
	for (m=0;m<480;m+=puzzle_bylen)
		for (n=0;n<640;n+=puzzle_bxlen) {
			iblock[c].x=n;
			iblock[c].y=m;
			iblock[c].w=puzzle_bxlen;
			iblock[c].h=puzzle_bylen;
			c++;
		}
	return(0);
}

void
free_blocks(void)
{
	free(iblock);
}

int
draw_block(int bn, int x, int y)
{
	SDL_Rect r;

	r.x=x*puzzle_bxlen;
	r.y=y*puzzle_bylen;
	
	SDL_BlitSurface(image,&iblock[bn],window,&r);

	return(0);
}

int
make_puzzle(void)
{
	int n,*tp,bl;

	puzzle=(int *)malloc(sizeof(int)*nblocks);
	if ( !puzzle ) {
		printf("ERROR: not enought memory for puzzle\n");
		exit(1);
	}

	tp=(int *)malloc(sizeof(int)*nblocks);
	if ( !tp ) {
		printf("ERROR: not enought memory\n");
		exit(1);
	}


	for (n=0;n<nblocks;n++)
		tp[n]=n;

	srand(time(NULL));

	for (n=0;n<nblocks;n++) {
		do {
			bl=(int)(((float)nblocks*rand())/RAND_MAX);
		} while (tp[bl]<0);
		puzzle[n]=tp[bl];
		tp[bl]=-1;
	}

	return(0);
}

int
draw_puzzle(void)
{
	SDL_Rect r;
	int c,x,y;
	
	c=0;
	for (y=0;y<puzzle_ylen;y++)
		for (x=0;x<puzzle_xlen;x++) {
			draw_block(puzzle[c],x,y);
			c++;
		}


	r.x = r.y = 0;
	r.w = 640;
	r.h = 480;
	SDL_UpdateRects(window,1,&r);
}

void
swap_blocks(int bfrom, int bto)
{
	int t;
	t=puzzle[bfrom];
	puzzle[bfrom]=puzzle[bto];
	puzzle[bto]=t;
}

void
mark_selected(int b)
{
	int x,y,n;
	Uint32 color;
	Uint8 *p;
	Uint16 *tp;
	
	printf("entro\n");

	color=SDL_MapRGB(window->format,0,0xff,0xff);
	if ( SDL_MUSTLOCK(window) )
		if ( SDL_LockSurface(window) < 0 ) {
			printf("Cant lock\n");
			return; //cant lock
		}

	x=(b % puzzle_ylen);
	y=(b / puzzle_ylen);

	printf("b=%d x=%d y=%d color=%x\n",b,x,y,color);
	y*=puzzle_bylen;
	x*=puzzle_bxlen;
	printf("b=%d x=%d y=%d\n",b,x,y);


	printf("bpp=%d\n",window->format->BytesPerPixel);

	p=(Uint8 *)window->pixels + y * window->pitch + x * window->format->BytesPerPixel;
	

//	*(Uint32 *)p=(Uint32)color;
	tp=window->pixels;
	*tp=color;
	for (n=128;n;n--) {
//		*tp=color;
		tp++;
	}
	


	if ( SDL_MUSTLOCK(window) )
		SDL_UnlockSurface(window);
}
