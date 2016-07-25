
#include <iostream>
#include <string>
#include <algorithm>
#include "SDL/SDL.h"

#include <stdint.h>

#include "VideoInput.hpp"

using namespace std;

void diff_buffer(void * a, void * b, void * dest, unsigned len)
{
    uint8_t * s1 = static_cast<uint8_t*>(a);
    uint8_t * s2 = static_cast<uint8_t*>(b);
    uint8_t * de = static_cast<uint8_t*>(dest);
    
    do
    {
//        *de = (*s1 - *s2)/2;
//        *de = 256-((256 + (*s1 - *s2))/2) ;
        int v1 = *s1;
        int v2 = *s2;
        int dif = v2 - v1;
        
        if ( dif < 0 ) dif = -dif;
        *de = dif & 0xff;
//        *de = dif < 32 ? 0 : 255;

//        *de = std::min(0,dif);
        ++de;
        ++s1;
        ++s2;
    } while ( --len );
}

void avg_buffer(void * a, void * b, void * dest, unsigned len)
{
    uint8_t * s1 = static_cast<uint8_t*>(a);
    uint8_t * s2 = static_cast<uint8_t*>(b);
    uint8_t * de = static_cast<uint8_t*>(dest);
    
    do
    {
        int v1 = *s1;
        int v2 = *s2;
        int avg = (v1 + (v1 >> 1)+ v2 + v2 + (v2>>1)) >> 2;
        
        *de = avg & 0xff;
//        *de = std::min(0,dif);
        ++de;
        ++s1;
        ++s2;
    } while ( --len );
}

void noise_redux(void * a, void * dest)
{
    uint8_t * s = static_cast<uint8_t*>(a);
    uint8_t * de = static_cast<uint8_t*>(dest);
 
//    s += 640+1;
    de += VIDEOW+1;
    for ( int n = 0; n < (VIDEOW*480)-(VIDEOW*2)-4; ++n )
    {
        *de = ((s[0]  >>2) + (s[1]>>1)    + (s[2]>>2)
            + (s[VIDEOW] >>1) + (s[VIDEOW+1]<<1)       + (s[VIDEOW+2]>>1)
            + (s[VIDEOW*2]>>2) + (s[VIDEOW*2+1]>>1) + (s[VIDEOW*2+2]>>2) ) /5;
        s++;
        de++;
    }
}

void to16gray(void * a, void * dest)
{
    uint8_t * s = static_cast<uint8_t*>(a);
    uint8_t * de = static_cast<uint8_t*>(dest);

    for ( int n = 0; n < (VIDEOW*VIDEOH); ++n )
    {
//        *de = (*s >> 4)<<4;
        *de = *s &0xf0;
        s++;
        de++;
    }
}

void morf_buffer(void * from, void * to, int rate)
{
    uint8_t * fr = static_cast<uint8_t*>(from);
    uint8_t * ori = static_cast<uint8_t*>(to);

    int orirate = rate;
    int frate = 100-rate;

    for ( int n = 0; n < (VIDEOW*VIDEOH); ++n )
    {
//        *de = (*s >> 4)<<4;
        int v = ((*ori * orirate) + (*fr * frate))/100;


        *ori = v&0xff;
        fr++;
        ori++;
    }
}

void morfsimple_buffer(void * from, void * to)
{
    uint8_t * fr = static_cast<uint8_t*>(from);
    uint8_t * ori = static_cast<uint8_t*>(to);

    for ( int n = 0; n < (VIDEOW*VIDEOH); ++n )
    {
        if ( *ori < *fr )
        {
            *ori += 1;
        }
        else if ( *ori > *fr )
        {
            *ori -= 1;
        }
        
//        *de = (*s >> 4)<<4;
//        int v = ((*ori * orirate) + (*fr * frate))/100;


//        *ori = v&0xff;
        fr++;
        ori++;
    }
}

uint8_t average_block(void* b, const SDL_Rect& r)
{
    uint8_t * ptr = static_cast<uint8_t*>(b);
    
    uint8_t * p = ptr + (r.y * VIDEOW) + r.x;
    
    unsigned int v = 0;
    
    for (int y = 0; y < r.h; ++y )
    {
        uint8_t * p = ptr + ((r.y+y) * VIDEOW) + r.x;
        for ( int x = 0; x < r.w; ++x )
        {
            v += *p++;
        }
    }
    
    return (v/(r.w*r.h))&0xff;
}

void filter_threshold(void * a, void * dest, int th)
{
    uint8_t * s = static_cast<uint8_t*>(a);
    uint8_t * de = static_cast<uint8_t*>(dest);

    for ( int n = 0; n < (VIDEOW*VIDEOH); ++n )
    {
//        *de = (*s >> 4)<<4;
        *de = *s < th ? 0 : 255;
        s++;
        de++;
    }
}

void filter_erosion( void* s, void *d, int r)
{
    int x,y;
    int tmp_x, tmp_y;
    int tmp_x_end, tmp_y_end;
    
    uint8_t min_val = 255;
    
    uint8_t * src = static_cast<uint8_t*>(s);
    uint8_t * dst = static_cast<uint8_t*>(d);
    
    for ( y = 0; y < VIDEOH; ++y )
    {
        tmp_y = std::max(0, y - r);
        tmp_y_end = std::min(VIDEOH, y + r);
        
        for ( x = 0; x < VIDEOW; ++x )
        {
            min_val = 255;
            tmp_x = std::max(0, x - r);
            tmp_x_end = std::min(VIDEOW, x + r);
            
            for ( int oy = tmp_y; oy < tmp_y_end; oy++ )
            {
                for ( int ox = tmp_x; ox < tmp_x_end; ox++ )
                {
                    min_val = std::min(min_val, src[oy*VIDEOW + x]);
                }
            }
            
            *dst++ = min_val;
        }
    }
    
}

void draw_hline(SDL_Surface *s, Uint32 c, int x, int y, int w)
{
    SDL_Rect r = { x, y, w, 1};
    SDL_FillRect(s,&r,c);
}

int main (int argc, char **argv)
{
    VideoInput vi;
    
    vi.openDevice("/dev/video0");
    vi.beginCapture();

    if ( SDL_Init(SDL_INIT_VIDEO) == -1 )
    {
        cout << "Error init sdl" << endl;
        return 1;
    }

    SDL_Surface *vid = SDL_SetVideoMode(640*2, 480*2, 32, SDL_SWSURFACE);

    SDL_Event eve;
    
//    Uint32 cyellow = SDL_MapRGB(vid->format,0xff,0xff,0);

//    SDL_Surface *s = SDL_CreateRGBSurface(SDL_SWSURFACE,640,480,24,0xff0000,0x00ff00,0x0000ff,0);
    
    SDL_Surface *base_frame = SDL_CreateRGBSurface(SDL_SWSURFACE, VIDEOW, VIDEOH, 8, 0, 0, 0, 0);
    SDL_Surface *base_frame_denoised = SDL_CreateRGBSurface(SDL_SWSURFACE, VIDEOW, VIDEOH, 8, 0, 0, 0, 0);

    SDL_Surface *dest   = SDL_CreateRGBSurface(SDL_SWSURFACE, VIDEOW, VIDEOH, 8, 0, 0, 0, 0);
    SDL_Surface *avgframe = SDL_CreateRGBSurface(SDL_SWSURFACE, VIDEOW, VIDEOH, 8, 0, 0, 0, 0);
    
    SDL_Surface *original = SDL_CreateRGBSurface(SDL_SWSURFACE, VIDEOW, VIDEOH, 8, 0, 0, 0, 0);
    SDL_Surface *difference = SDL_CreateRGBSurface(SDL_SWSURFACE, VIDEOW, VIDEOH, 8, 0, 0, 0, 0);
    SDL_Surface *filtered = SDL_CreateRGBSurface(SDL_SWSURFACE, VIDEOW, VIDEOH, 8, 0, 0, 0, 0);
    SDL_Surface *eroded = SDL_CreateRGBSurface(SDL_SWSURFACE, VIDEOW, VIDEOH, 8, 0, 0, 0, 0);
    SDL_Surface *eroded2 = SDL_CreateRGBSurface(SDL_SWSURFACE, VIDEOW, VIDEOH, 8, 0, 0, 0, 0);
    
    
    SDL_Color pcolors[256];
    
    for ( int n = 0; n < 256; n++)
    {
        pcolors[n].r = n;
        pcolors[n].g = n;
        pcolors[n].b = n;
    }
    
    SDL_SetColors(base_frame, pcolors, 0, 256);
    SDL_SetColors(dest, pcolors, 0, 256);
    SDL_SetColors(avgframe, pcolors, 0, 256);
    
    SDL_SetColors(original, pcolors, 0, 256);
    SDL_SetColors(difference, pcolors, 0, 256);
    SDL_SetColors(filtered, pcolors, 0, 256);
    SDL_SetColors(eroded, pcolors, 0, 256);
    SDL_SetColors(eroded2, pcolors, 0, 256);
    
    uint8_t* base_frame_buffer = static_cast<uint8_t*>(base_frame->pixels);
    uint8_t* base_frame_denoised_buffer = static_cast<uint8_t*>(base_frame_denoised->pixels);
    
    uint8_t* original_buffer   = static_cast<uint8_t*>(original->pixels);
    uint8_t* difference_buffer = static_cast<uint8_t*>(difference->pixels);
    uint8_t* filtered_buffer   = static_cast<uint8_t*>(filtered->pixels);
    uint8_t* eroded_buffer   = static_cast<uint8_t*>(eroded->pixels);
    uint8_t* eroded2_buffer   = static_cast<uint8_t*>(eroded2->pixels);

    
    vi.captureFrame();
    SDL_Delay(1000);
    vi.captureFrame();
    SDL_Delay(1000);
    vi.captureFrame();
//    SDL_Delay(1000);
//    vi.captureFrame();
    vi.frameYToBuffer8(base_frame_buffer);

    noise_redux(base_frame_buffer, base_frame_denoised_buffer);
    
//    memcpy(avg1, frame1->pixels, 640*480);

    SDL_Rect drect = {0};
    
//    SDL_Rect tr = { 540, 380, 50, 50 };
    
//    uint8_t avg = average_block(frame1->pixels, tr);
//    SDL_FillRect(frame1,&tr, avg);

//    memcpy(avg1, frame1->pixels, 640*480);
    
    int threshold = 20;
    int erosion = 1;
    int rate = 75;
    unsigned int morfevery = 1;
    unsigned int morfcount = 1;
    
    bool running = true;
    while ( running )
    {
        while ( SDL_PollEvent(&eve) )
        {
            switch ( eve.type )
            {
                case SDL_QUIT:
                    running = false;
                    break;
                    
                case SDL_KEYUP:
                    switch ( eve.key.keysym.sym )
                    {
                        case SDLK_z:
                            if ( --threshold < 0 ) threshold = 0;
                            cout << "Threshold is " << threshold << endl;
                            break;
                        case SDLK_x:
                            if ( ++threshold > 255 ) threshold = 255;
                            cout << "Threshold is " << threshold << endl;
                            break;
                            
                        case SDLK_c:
                            if ( --erosion < 0 ) erosion = 0;
                            cout << "Erosion is " << erosion << endl;
                            break;
                        case SDLK_v:
                            if ( ++erosion > 255 ) erosion = 255;
                            cout << "Erosion is " << erosion << endl;
                            break;
                            
                        case SDLK_a:
                            if ( --rate < 0 ) rate  = 0;
                            cout << "Rate  is " << rate  << endl;
                            break;
                        case SDLK_s:
                            if ( ++rate  > 255 ) rate  = 255;
                            cout << "Rate  is " << rate  << endl;
                            break;
                        
                        case SDLK_d:
                            --morfevery;
//                            if ( --morfevery < 0 ) morfevery  = 0;
                            cout << "morfevery  is " << morfevery  << endl;
                            break;
                        case SDLK_f:
                            ++morfevery;
//                            if ( ++morfevery  > 255 ) morfevery  = 255;
                            cout << "morfevery  is " << morfevery  << endl;
                            break;
                        default:;
                    }
                    break;
                default:;
            }
        }

        if ( vi.captureFrame() )
        {
    
//            SDL_LockSurface(gsurface);

//            vi.frameToGrey8(frame2->pixels);

            vi.frameYToBuffer8(original_buffer);
            diff_buffer(base_frame_buffer, original_buffer, difference_buffer, VIDEOW*VIDEOH);
            filter_threshold(difference_buffer, filtered_buffer, threshold);
            
            filter_erosion(filtered_buffer, eroded_buffer, erosion);
            filter_erosion(eroded_buffer, eroded2_buffer, erosion);
            
            if ( ++morfcount >= morfevery )
            {
                morfcount = 0;
                morf_buffer(original_buffer, base_frame_buffer, rate);
//                morfsimple_buffer(original_buffer, base_frame_buffer);                
            }
            
            
        }

        SDL_FillRect(vid, 0, 0);

        drect.x = 0;
        drect.y = 0;

        SDL_BlitSurface(original, 0, vid, &drect);
        
        drect.x = VIDEOW;
        SDL_BlitSurface(filtered, 0, vid, &drect);

        drect.x = 0;
        drect.y = VIDEOH;
        SDL_BlitSurface(eroded,0,vid, &drect);

        drect.x = VIDEOW;
        SDL_BlitSurface(eroded2,0,vid, &drect);


//        draw_hline(vid, cyellow, tr.x, tr.y, tr.w);
//        
//        draw_hline(vid, cyellow, tr.x, tr.y+tr.h, tr.w);
//
//        draw_hline(vid, cyellow, tr.x+640, tr.y, tr.w);
//        
//        draw_hline(vid, cyellow, tr.x+640, tr.y+tr.h, tr.w);

        SDL_UpdateRect(vid, 0, 0, 0, 0);

    }

    vi.endCapture();
    
    vi.closeDevice();

//    stop_capturing(cam);
//    uninit_device(cam);
//    close(cam);

    SDL_Quit();
    
    

    return 0;
}

