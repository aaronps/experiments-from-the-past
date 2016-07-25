/* 
 * File:   SourceReader.hpp
 * Author: krom
 *
 * Created on November 26, 2012, 8:40 PM
 */

#ifndef SOURCEREADER_HPP
#define	SOURCEREADER_HPP

#include <stdint.h>
#include "SourceCharacter.hpp"

class SourceReader
{
    uint8_t * buffer;
    int len;
    int pos;
public:
    SourceReader(uint8_t* buffer, int len) : buffer(buffer), len(len), pos(0){}
    
    inline bool hasMore() const { return pos < len; }
    
    inline SourceCharacter readNext() { return hasMore() ? buffer[pos++] : 0; }
    
};

#endif	/* SOURCEREADER_HPP */

