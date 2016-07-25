/* 
 * File:   JsLexer.hpp
 * Author: krom
 *
 * Created on November 15, 2012, 10:54 PM
 */

#ifndef JSLEXER_HPP
#define	JSLEXER_HPP

#include <string>
#include <list>
#include <stdint.h>

#include "SourceCharacter.hpp"

class SourceReader;

class JsLexer
{
    std::list<std::string> tokens;
    struct States
    {
        enum TYPE
        {
            UNDECIDED_STATE = 0,
            OPDIV,
            MULTI_LINE_COMMENT,
            MULTI_LINE_COMMENT_MAYFINISH,
            MULTI_LINE_COMMENT_NEWLINE,
            MULTI_LINE_COMMENT_NEWLINE_MAYFINISH,
            SINGLE_LINE_COMMENT,
            
            IDENTIFIER,
            NUMBER,
            DOUBLESTRING,
            DOUBLESTRINGESCAPE,
            SINGLESTRING,
            SINGLESTRINGESCAPE,
            OPPLUS,
            OPMINUS,
            OPMUL,
            
            OPOR,
            OPNOT,
            OPNOTEQ,
            OPLESS,
            OPGREAT,
            OPAND,
            OPQUESTION,
            REGEX,
            

            ERROR
        };
    };
    
    States::TYPE state;
    
    int line_num;
    
    std::string current_element;
    
public:
    JsLexer() : state(States::UNDECIDED_STATE) {}
    
    void parseChunk(SourceReader& source);
    
    // return true to repeat the state
    template<States::TYPE T> void state_func(const SourceCharacter c, SourceReader& source);
    
};

#endif	/* JSLEXER_HPP */
