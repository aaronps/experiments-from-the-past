/* 
 * File:   main.c
 * Author: krom
 *
 * Created on February 9, 2012, 8:28 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "SDL.h"

typedef struct
{
    int size;
    int offset;
    uint8_t data[1];
} pcm_data;

pcm_data* dump_wav(const char * filename)
{
    FILE *f = fopen(filename, "rb");
    if ( !f )
    {
        printf("File '%s' not found", filename);
        return 0;
    }
    
    char    chunk_id[5] = {0};
    int32_t chunk_size  = 0;
    char    head_format[5] = {0};
    
    fread( chunk_id, 4, 1, f);
    fread( &chunk_size, 4, 1, f);
    int32_t total_size = chunk_size;
    
    fread( head_format, 4, 1, f);
    
    printf("[head chunk: '%s' size-no-head: %u format: '%s']\n", chunk_id, chunk_size, head_format);
    
    fread( chunk_id, 4, 1, f);
    fread( &chunk_size, 4, 1, f);
    printf("[Chunk: '%s' size: %u]\n", chunk_id, chunk_size);
    
    struct
    {
        int16_t audio_format;
        int16_t num_channels;
        int32_t sample_rate;
        int32_t byte_rate;
        int16_t block_align;
        int16_t bits_per_sample;
    } wav_fmt __attribute__((packed));
  
    printf("[Size of simple header: %u]\n", sizeof(wav_fmt));
    
    fread( &wav_fmt, sizeof(wav_fmt), 1, f);
    
    printf("Audio Format: %d\n", wav_fmt.audio_format);
    printf("Channels: %d\n", wav_fmt.num_channels);
    printf("Sample Rate: %d\n", wav_fmt.sample_rate);
    printf("Byte Rate: %d\n", wav_fmt.byte_rate);
    printf("Block Align: %d\n", wav_fmt.block_align);
    printf("Bits Per Sample: %d\n", wav_fmt.bits_per_sample);
/*
    printf(": %d\n", wav_fmt.);
*/
    
    fread( chunk_id, 4, 1, f);
    fread( &chunk_size, 4, 1, f);
    printf("[Chunk: '%s' size: %u]\n", chunk_id, chunk_size);
    
    pcm_data* data = malloc(chunk_size + sizeof(pcm_data)-1);
    data->size = chunk_size;
    data->offset = 0;
    fread( data->data, chunk_size, 1, f);
    
    fclose(f);
    
    return data;
}

typedef struct
{
    SDL_AudioSpec* hw_audio_format;
    pcm_data* data1;
    pcm_data* data2;
} mix_data;

char running1 = 0;
char running2 = 0;

void SDLCALL on_more_audio( void * userdata, Uint8* stream, int len)
{
/*
    mix_data* mdata = (mix_data*)userdata;
    pcm_data* data = mdata->data2;
    int remain = len;
    int can_copy = data->size - data->offset;
    int to_copy = (remain < can_copy) ? remain : can_copy;
    if ( to_copy )
    {
        memcpy(stream, &(data->data[data->offset]), to_copy );
        data->offset += to_copy;
        remain -= to_copy;
    }
    
    if ( remain )
    {
        memset(stream+to_copy, mdata->hw_audio_format->silence, remain);
    }
    
    if ( remain == len ) { running1 = 0; }
    return;
*/
    

    mix_data* mdata = (mix_data*)userdata;
    
    pcm_data* data1 = mdata->data1;
    pcm_data* data2 = mdata->data2;
    
    int remain = len;
    
    int remain_data1 = data1->size - data1->offset;
    int remain_data2 = data2->size - data2->offset;
    
    if ( ! remain_data1 && ! remain_data2 )
    {
        running1 = 0;
        running2 = 0;
        memset(stream, mdata->hw_audio_format->silence, len);
    }
    else if ( ! remain_data2 )
    {
        // copy channel 1;
        int to_copy = (remain < remain_data1) ? remain : remain_data1;
        printf("copy channel 1 [%d]\n", to_copy);
        memcpy(stream, &(data1->data[data1->offset]), to_copy );
        data1->offset+=to_copy;
        if ( to_copy < len )
        {
            running1 = 0;
            memset(stream+len-to_copy, mdata->hw_audio_format->silence, len-to_copy);
        }
    }
    else if ( ! remain_data1 )
    {
        // copy channel 2;
        int to_copy = (remain < remain_data2) ? remain : remain_data2;
        memcpy(stream, &(data2->data[data2->offset]), to_copy );
        data2->offset+=to_copy;
        if ( to_copy < len )
        {
            running2 = 0;
            memset(stream+len-to_copy, mdata->hw_audio_format->silence, len-to_copy);
        }
    }
    else
    {
        printf("mixing %d\n", len);
        // mix them
        uint8_t* dst = stream;
        
        uint8_t* s1 = &(data1->data[data1->offset]);
        int s1rem = remain_data1;
        
        uint8_t* s2 = &(data2->data[data2->offset]);
        int s2rem = remain_data2;
        
        unsigned int val;
        unsigned int v1;
        unsigned int v2;
        
/*
        memcpy(stream, &(data1->data[data1->offset]), len);
        data1->offset += len;
*/

       
        do
        {
            if ( s1rem && s2rem )
            {
                v1 = *s1;
                v2 = *s2;
                if ( v1 < 128 && v2 < 128 )
                {
                    val = (v1*v2)>>7;
                }
                else
                {
                    val = 2*(v1+v2) - ((v1*v2)>>7) - 256;
                }

                *dst = (val&0xff);
                
                s1++;
                s2++;
                data1->offset++;
                data2->offset++;
                if ( ! --s1rem )
                {
                    printf("s1finish\n");
                    running1 = 0;
                }
                if ( ! --s2rem )
                {
                    printf("s2finish\n");
                    running2 = 0;
                }
            }
            else if ( s1rem )
            {
                *dst = *s1;
                s1++;
                data1->offset++;
                if ( ! --s1rem )
                {
                    running1 = 0;
                }
            }
            else if ( s2rem )
            {
                *dst = *s2;
                s2++;
                data2->offset++;
                if ( ! --s2rem )
                {
                    running2 = 0;
                }
            }
            else
            {
                *dst = mdata->hw_audio_format->silence;
            }
            
            dst++;
        } while ( --len );

    }
}

/*
 * 
 */
int main(int argc, char** argv)
{
    if ( argc < 3 )
    {
        printf("Use: %s <filename1.wav> <filename2.wav>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    printf("Starting...\n");

    pcm_data* data1 = dump_wav(argv[1]);
    if ( !data1 )
    {
        printf("'%s' NOT LOADED!\n", argv[1]);
        return EXIT_FAILURE;
    }

    pcm_data* data2 = dump_wav(argv[2]);
    if ( !data2 )
    {
        printf("'%s' NOT LOADED!\n", argv[2]);
        free(data1);
        return EXIT_FAILURE;
    }
    
    SDL_Init(SDL_INIT_AUDIO);
    
    char audio_driver_buf[256] = {0};
    const char * audio_driver = SDL_AudioDriverName( audio_driver_buf, sizeof(audio_driver_buf)-1);
    if ( audio_driver )
    {
        printf("Audio driver used: '%s'\n", audio_driver);
    }
    else
    {
        printf("Audio driver not loaded\n");
    }
    
    SDL_AudioSpec desired = {0};
    SDL_AudioSpec obtained = {0};
    
    mix_data md;
    
    md.hw_audio_format = &obtained;
    md.data1 = data1;
    md.data2 = data2;
    
    desired.freq = 11025;
    desired.format = AUDIO_U8;
    desired.samples = 1024;
    desired.channels = 1;
    desired.userdata = &md;
    desired.callback = on_more_audio;
    
    if ( SDL_OpenAudio(&desired, &obtained) == -1 )
    {
        printf("Error opening audio: '%s'\n", SDL_GetError());
    }
    else
    {
        printf("[Obtained]\n");
        printf("Frequency: %d [%d]\n", obtained.freq, desired.freq);
        printf("Format: %d [%d]\n", obtained.format, desired.format);
        printf("Samples: %d [%d]\n", obtained.samples, desired.samples);
        printf("Channels: %d [%d]\n", obtained.channels, desired.channels);
        printf("Buffer size: %d\n", obtained.size);
        printf("Silence: %d\n", obtained.silence);
    }
    
    running1 = 1;
    running2 = 1;
    SDL_PauseAudio(0);
    while ( running1|running2 )
    {
        SDL_Delay(100);
    }
    
    printf("End of sound\n");
    
    SDL_Delay(100);
    SDL_Quit();

    free(data1);
    free(data2);
    printf("Finished\n");
    return (EXIT_SUCCESS);
}

