#define _GNU_SOURCE

#include <stdio.h>
#include <dlfcn.h>
#include <SDL/SDL.h>

#define MAKE_FUNC(name) static void * (*func)(); \
		if (!func) func=dlsym(RTLD_NEXT,name);

int
close (int fd) 
{
	MAKE_FUNC("close");
	putchar('X');
	return(func(fd));

}


void *
calloc(size_t n, size_t size)
{
	void *val;
	static int working=0;
	static void *(*func)();
	if (working) {
		printf("CALLOC called twice (%d,%d) returning NULL\n",n,size);
		return(0);
	}
	working=1;
	if (!func)
		func=dlsym(RTLD_NEXT,"calloc");
//	MAKE_FUNC("calloc");
	printf("calloc %d,%d = ", n,size);
	val=func(n,size);
	printf("%08x\n",val);
	working=0;
	return(val);
}

void *
malloc(size_t size)
{
	void *val;
	MAKE_FUNC("malloc");
	printf("malloc %d = ", size);     
	val=func(size);
	printf("%08x\n",val);
	return(val);
}

void
free(void *p)
{
	MAKE_FUNC("free");
	printf("free %08x\n", p);
	func(p);
}

void *
realloc(void *p, size_t size)
{
	void *val;
	MAKE_FUNC("realloc");
	printf("realloc %08x %d = ", p,size);
	val=func(p,size);
	printf("%08x\n",val);
	return(val);
}

void 
SDL_FreeSurface (SDL_Surface *p)
{
	MAKE_FUNC("SDL_FreeSurface");
	printf("SDL_FreeSurface %08x\n",p);
	func(p);
	printf("SDL_FreeSurface exit\n");
}

SDL_Surface *
SDL_CreateRGBSurface (Uint32 flags, int width, int height, int depth,
		Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask)
{
	SDL_Surface *s;
	MAKE_FUNC("SDL_CreateRGBSurface");

	printf("SDL_CreateRGBSurface %08x %d,%d,%d %x,%x,%x,%x\n",
		flags,width,height,depth,Rmask,Gmask,Bmask,Amask);
	s=func( flags,width,height,depth,Rmask,Gmask,Bmask,Amask);
	printf("SDL_CreateRGBSurface %08x exit\n",s);
	return(s);
}

SDL_Surface *
SDL_ConvertSurface (SDL_Surface *orig, SDL_PixelFormat *format, Uint32 flags)
{
	SDL_Surface *s;
	MAKE_FUNC("SDL_ConvertSurface");

	printf("SDL_ConvertSurface %08x %08x %08x\n", orig,format,flags);
	s=func(orig,format,flags);
	printf("SDL_ConvertSurface %08x exit\n",s);
	return(s);
}

SDL_Surface *
SDL_DisplayFormat(SDL_Surface *orig)
{
	SDL_Surface *s;
	MAKE_FUNC("SDL_DisplayFormat");

	printf("SDL_DisplayFormat %08x\n", orig);
	s=func(orig);
	printf("SDL_DisplayFormat %08x exit\n", s);
	return(s);
}

SDL_Surface *
SDL_DisplayFormatAlpha(SDL_Surface *orig)
{
	SDL_Surface *s;
	MAKE_FUNC("SDL_DisplayFormatAlpha");

	printf("SDL_DisplayFormatAlpha %08x\n", orig);
	s=func(orig);
	printf("SDL_DisplayFormatAlpha %08x exit\n", s);
	return(s);
}

SDL_Surface *
SDL_GetVideoSurface(void)
{
	SDL_Surface *s;
	MAKE_FUNC("SDL_GetVideoSurface");

	s=func();
	printf("SDL_GetVideoSurface %08x\n",s);
	return(s);
}

SDL_Surface *
SDL_SetVideoMode(int w, int h, int b, Uint32 f)
{
	SDL_Surface *s;
	MAKE_FUNC("SDL_SetVideoMode");

	printf("SDL_SetVideoMode %d,%d,%d %08x\n",w,h,b,f);
	s=func(w,h,b,f);
	printf("SDL_SetVideoMode %08x\n",s);
	return(s);
}


SDL_Surface *
SDL_CreateRGBSurfaceFrom(void *p, int w, int h, int d, int pi,
		Uint32 rm, Uint32 gm, Uint32 bm, Uint32 am)
{
	SDL_Surface *s;
	MAKE_FUNC("SDL_CreateRGBSurfaceFrom");

	printf("SDL_CreateRGBSurfaceFrom %08x %d,%d,%d,%d %x,%x,%x,%x\n",
		p,w,h,d,pi,rm,gm,bm,am);
	s=func(p,w,h,d,pi,rm,gm,bm,am);
	printf("SDL_CreateRGBSurfaceFrom %08x\n",s);
	return(s);
}

int
RLEAlphaSurface(SDL_Surface *sur)
{
	int res;
	MAKE_FUNC("RLEAlphaSurface");

	printf("RLEAlphaSurface %08x\n",sur);
	res=(int)func(sur);
	return(res);
}


