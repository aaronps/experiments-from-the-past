/* 
 * File:   SourceCharacter.hpp
 * Author: krom
 *
 * Created on November 27, 2012, 7:34 PM
 */

#ifndef SOURCECHARACTER_HPP
#define	SOURCECHARACTER_HPP

#include <stdint.h>

#define SourceCharacter8bit

#ifdef SourceCharacter8bit
typedef uint8_t SourceCharacter;
#else
typedef uint16_t SourceCharacter;
#endif

struct SourceCharacterTraits
{
    // 7.2 White Space
    // Still missing: "any other unicode category Z?"
    static inline bool isWhiteSpace( SourceCharacter c )
    {
        switch ( c )
        {
            case 0x09: // tab
            case 0x0b: // vertial tab
            case 0x0c: // form feed
            case 0x20: // space
            case 0xa0: // no break space
#ifndef SourceCharacter8bit
            case 0xfeff: // BOM
#endif
                return true;
        }
        return false;
    }
    
    // 7.3 Line Terminators
    // Still missing: cr+lf = only one line terminator
    static inline bool isLineTerminator( SourceCharacter c )
    {
        switch ( c )
        {
            case 0x0a: // lf
            case 0x0d: // cr
#ifndef SourceCharacter8bit
            case 0x2028: // line separator
            case 0x2029: // paragraph separator
#endif
                return true;
        }
        return false;
    }
};

#endif	/* SOURCECHARACTER_HPP */
