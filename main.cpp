/* 
 * File:   main.cpp
 * Author: krom
 *
 * Created on October 22, 2012, 10:34 PM
 */

#include <iostream>
#include <string>
#include <cstdio>

namespace BASE64
{
    
    static const char binToBase64Map[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    
    const std::string& toBase64(const char * in, const int len)
    {
        std::string res((((len)+2)/3)*4, '=');
        
        uint32_t value;
        
        int remain = len;
        int pos = 0;
        
        for ( ; remain >= 3; remain-=3 )
        {
            value = (*(in++) << 16) | (*(in++) << 8) | *(in++);
                    
            res[pos++] = binToBase64Map[value >> 18];
            res[pos++] = binToBase64Map[(value >> 12) & 0x3f];
            res[pos++] = binToBase64Map[(value >> 6) & 0x3f];
            res[pos++] = binToBase64Map[value & 0x3f];
            
            
        }
        
        a = v1;
        r[a];
        
        a<<=4;
        a|= v2 << 4;
        r[a];
        
        a = v2 << 2 | v3 >> 6;
        r[a];
        
        a = v3;
        r[a];
        
        
        return res;
    }
    
    
    
    
}


/*
 * 
 */
int main(int argc, char** argv)
{
    const unsigned char bb[4] = { 0xde, 0xad, 0xbe, 0xef };
    
    union
    {
        const unsigned char * uchar;
        const unsigned int * uint;
    } data;
    
    data.uchar = bb;
    
    unsigned int ival = *data.uint;
    
    printf("Value is '%x'", ival);
    
    return 0;
}

