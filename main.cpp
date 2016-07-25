/* 
 * File:   main.cpp
 * Author: krom
 *
 * Created on December 22, 2012, 5:59 PM
 */

#include <cstdlib>
#include <cstdio>

#include <stdint.h>
#include <string.h>
#include <stdio.h>

using namespace std;

#define KK0 (0x5A827999)
#define KK1 (0x6ED9EBA1)
#define KK2 (0x8F1BBCDC)
#define KK3 (0xCA62C1D6)

const char b2h[17] = "0123456789abcdef";
const char b64[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

uint32_t table_1[10] =
{
    0x32353845, 0x41464135, 0x2d453931, 0x342d3437, 0x44412d39, 0x3543412d,
    0x43354142, 0x30444338, 0x35423131, 0x80000000
};

uint32_t table[80] = 
{
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x000001e0, 0x00000000, 0x00000000,
    0x000003c0, 0x00000000, 0x00000000, 0x00000780, 0x00000000, 0x000003c0,
    0x00000f00, 0x00000000, 0x00000000, 0x00001e00, 0x00000000, 0x00000cc0,
    0x00003c00, 0x00000440, 0x00000000, 0x00007800, 0x00000f00, 0x00003300,
    0x0000f000, 0x00000f00, 0x00000000, 0x0001ef00, 0x00000000, 0x0000cc00,
    0x0003c000, 0x00004380, 0x00000000, 0x00078f00, 0x0000ff00, 0x00032680,
    0x000f0000, 0x0000f000, 0x00003300, 0x001eff00, 0x00000000, 0x000cb800,
    0x003c0000, 0x00040b00, 0x0000f000, 0x0078ff00, 0x000ff000, 0x00338700,
    0x00f00000, 0x000fc300, 0x0000f000, 0x01efbb00, 0x00000000, 0x00cc0000,
    0x03c0f000, 0x00438000, 0x00000000, 0x078f0000, 0x00ff0000, 0x03269e00,
    0x0f000000, 0x00f0f000, 0x00333c00, 0x1eff8800, 0x00000000, 0x0cb88800,
    0x3c00f000, 0x040a4a00, 
};


class SHA1
{
public:
    SHA1()
    {
    }
    
    inline uint32_t rotate_1(uint32_t value)
    {
        return (value << 1) | (value >> 31);
    }
    
    inline uint32_t rotate_5(uint32_t value)
    {
        return (value << 5) | (value >> 27);
    }
    
    inline uint32_t rotate_30(uint32_t value)
    {
        return (value << 30) | (value >> 2);
    }
    
    void full(const uint8_t* data, const int len, uint8_t * out)
    {
        uint32_t W[80]
                ,tmp = len*8
                ,t
                ,A = 0x67452301
                ,B = 0xEFCDAB89
                ,C = 0x98BADCFE
                ,D = 0x10325476
                ,E = 0xC3D2E1F0;
                
        uint8_t buffer[64] = {0};
        if ( len )
        {
            memcpy(buffer, data, len);
            buffer[62] = (tmp>>8)&0xff;
            buffer[63] = tmp&0xff;
        }

        buffer[len] = 0x80;
        
        uint8_t *ptr = buffer;
        for ( t = 0; t < 16; t++ )
        {
            tmp  = *(ptr++) << 24;
            tmp |= *(ptr++) << 16;
            tmp |= *(ptr++) <<  8;
            tmp |= *(ptr++);
            W[t] = tmp;
        }
        
        for ( t = 16; t < 80; t++ )
        {
           W[t] = rotate_1(W[t-3] ^ W[t-8] ^ W[t-14] ^ W[t-16]);
        }
        
        uint32_t * p = &W[0];
        
#define BASE(F,K) tmp =  rotate_5(A) + (F) + E + (*(p++)) + (K); E=D; D=C; C=rotate_30(B); B=A; A=tmp;
#define G BASE((((C^D)&B)^D),                 0x5A827999)
#define R BASE((B ^ C ^ D),                   0x6ED9EBA1)
#define O BASE(((B & C) | (B & D) | (C & D)), 0x8F1BBCDC)
#define K BASE((B ^ C ^ D),                   0xCA62C1D6)
        G G G G G G G G G G G G G G G G G G G G
        R R R R R R R R R R R R R R R R R R R R
        O O O O O O O O O O O O O O O O O O O O
        K K K K K K K K K K K K K K K K K K K K
#undef K
#undef O
#undef R
#undef G
#undef BASE

        A += 0x67452301;
        B += 0xEFCDAB89;
        C += 0x98BADCFE;
        D += 0x10325476;
        E += 0xC3D2E1F0;

#define TOHEX(v) *(out++)= b2h[ v >> 28]; \
        *(out++)= b2h[(v >> 24) & 0xf]; \
        *(out++)= b2h[(v >> 20) & 0xf]; \
        *(out++)= b2h[(v >> 16) & 0xf]; \
        *(out++)= b2h[(v >> 12) & 0xf]; \
        *(out++)= b2h[(v >>  8) & 0xf]; \
        *(out++)= b2h[(v >>  4) & 0xf]; \
        *(out++)= b2h[ v        & 0xf]; 

        TOHEX(A)
        TOHEX(B)
        TOHEX(C)
        TOHEX(D)
        TOHEX(E)

#undef TOHEX
    }
    
    void websocket(const uint8_t* data, uint8_t * out)
    {
        uint32_t W[80]
                ,tmp
                ,A, FA = A = 0x67452301
                ,B, FB = B = 0xEFCDAB89
                ,C, FC = C = 0x98BADCFE
                ,D, FD = D = 0x10325476
                ,E, FE = E = 0xC3D2E1F0 ;
                
        for ( int n = 0; n < 6; n++ )
        {
            tmp  = *(data++) << 24;
            tmp |= *(data++) << 16;
            tmp |= *(data++) <<  8;
            tmp |= *(data++);
            W[n] = tmp;
        }
        
        memcpy(&W[6], table_1, sizeof(table_1));
        
        for ( int n = 16; n < 80; n++ )
        {
           W[n] = rotate_1(W[n-3] ^ W[n-8] ^ W[n-14] ^ W[n-16]);
        }
        
        uint32_t * p = W;
        
#define BASE(F,K) tmp =  rotate_5(A) + (F) + E + (*(p++)) + (K); E=D; D=C; C=rotate_30(B); B=A; A=tmp;
#define G BASE((((C^D)&B)^D),                 0x5A827999)
#define R BASE((B ^ C ^ D),                   0x6ED9EBA1)
#define O BASE(((B & C) | (B & D) | (C & D)), 0x8F1BBCDC)
#define K BASE((B ^ C ^ D),                   0xCA62C1D6)
        G G G G G G G G G G G G G G G G G G G G
        R R R R R R R R R R R R R R R R R R R R
        O O O O O O O O O O O O O O O O O O O O
        K K K K K K K K K K K K K K K K K K K K

        A = FA += A;
        B = FB += B;
        C = FC += C;
        D = FD += D;
        E = FE += E;
        
        p = table;
        
        G G G G G G G G G G G G G G G G G G G G
        R R R R R R R R R R R R R R R R R R R R
        O O O O O O O O O O O O O O O O O O O O
        K K K K K K K K K K K K K K K K K K K K
#undef K
#undef O
#undef R
#undef G
#undef BASE

        FA += A;
        FB += B;
        FC += C;
        FD += D;
        FE += E;

        *(out++) = b64[FA >> 26];
        *(out++) = b64[(FA >> 20) & 0x3f];
        *(out++) = b64[(FA >> 14) & 0x3f];
        *(out++) = b64[(FA >>  8) & 0x3f];
        *(out++) = b64[(FA >>  2) & 0x3f];
        
        *(out++) = b64[((FA&3) << 4)|((FB>>28)&0x0f)];
        
        *(out++) = b64[(FB >> 22) & 0x3f];
        *(out++) = b64[(FB >> 16) & 0x3f];
        *(out++) = b64[(FB >> 10) & 0x3f];
        *(out++) = b64[(FB >>  4) & 0x3f];

        *(out++) = b64[((FB&0xf) << 2)|((FC>>30)&0x03)];

        *(out++) = b64[(FC >> 24) & 0x3f];
        *(out++) = b64[(FC >> 18) & 0x3f];
        *(out++) = b64[(FC >> 12) & 0x3f];
        *(out++) = b64[(FC >>  6) & 0x3f];
        *(out++) = b64[FC & 0x3f];
        
        *(out++) = b64[FD >> 26];
        *(out++) = b64[(FD >> 20) & 0x3f];
        *(out++) = b64[(FD >> 14) & 0x3f];
        *(out++) = b64[(FD >>  8) & 0x3f];
        *(out++) = b64[(FD >>  2) & 0x3f];
        
        *(out++) = b64[((FD&3) << 4)|((FE>>28)&0x0f)];
        
        *(out++) = b64[(FE >> 22) & 0x3f];
        *(out++) = b64[(FE >> 16) & 0x3f];
        *(out++) = b64[(FE >> 10) & 0x3f];
        *(out++) = b64[(FE >>  4) & 0x3f];
        *(out++) = b64[(FE <<  2) & 0x3f];
        
        *(out++) = '=';
        
        *(out++) = 0;
        
    }
     
    
};

/*
 * 
 */
int main(int argc, char** argv)
{
//empty:
//  da 39 a3 ee 5e 6b 4b 0d 32 55 bf ef 95 60 18 90 af d8 07 09 
//abc:
//  a9 99 3e 36 47 06 81 6a ba 3e 25 71 78 50 c2 6c 9c d0 d8 9d 
//base:
//  2f d4 e1 c6 7a 2d 28 fc ed 84 9e e1 bb 76 e7 39 1b 93 eb 12 
    uint8_t buf[41];
    buf[40] = 0;
    SHA1 cc;
    
    cc.full((const uint8_t*)"", 0, buf);
    printf("empty\n  %s\n", buf);
    printf("  da39a3ee5e6b4b0d3255bfef95601890afd80709\n");
    
    cc.full((const uint8_t*)"abc", 3, buf);
    printf("abc\n  %s\n", buf);
    printf("  a9993e364706816aba3e25717850c26c9cd0d89d\n");
            
    cc.full((const uint8_t*)"The quick brown fox jumps over the lazy dog", strlen("The quick brown fox jumps over the lazy dog"), buf);
    printf("base\n  %s\n", buf);
    printf("  2fd4e1c67a2d28fced849ee1bb76e7391b93eb12\n");

    cc.websocket((const uint8_t*)"x3JJHMbDL1EzLkh9GBhXDw==", buf);
    printf("ws\n  %s\n", buf);
    printf("  HSmrc0sMlYUkAGmm5OPpG2HaGWk=\n");
    
    cc.websocket((const uint8_t*)"dGhlIHNhbXBsZSBub25jZQ==", buf);
    printf("ws2\n  %s\n", buf);
    printf("  s3pPLMBiTxaQ9kYGzzhZRbK+xOo=\n");
    
    return 0;
}

