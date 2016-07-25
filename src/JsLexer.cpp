#include "JsLexer.hpp"
#include "SourceReader.hpp"
#include "SourceCharacter.hpp"

#include <iostream>


template<>
inline void JsLexer::state_func<JsLexer::States::UNDECIDED_STATE>(const SourceCharacter c, SourceReader& source)
{
    if ( ! SourceCharacterTraits::isWhiteSpace(c) )
    {
        if ( c == '/' )
        {
            state = States::OPDIV;
        }
    }
}

template<>
inline void JsLexer::state_func<JsLexer::States::OPDIV>(const SourceCharacter c, SourceReader& source)
{
    if ( c == '*' )
    {
        current_element.clear();
        state = States::MULTI_LINE_COMMENT;
    }
    else if ( c == '/' )
    {
        current_element.clear();
        state = States::SINGLE_LINE_COMMENT;
    }
    else
    {
        state = States::UNDECIDED_STATE;
    }
}

template<>
inline void JsLexer::state_func<JsLexer::States::MULTI_LINE_COMMENT>(const SourceCharacter c, SourceReader& source)
{
    if ( c == '*' )
    {
        state = States::MULTI_LINE_COMMENT_MAYFINISH;
    }
    else if ( SourceCharacterTraits::isLineTerminator(c) )
    {
        current_element += '\n';
        state = States::MULTI_LINE_COMMENT_NEWLINE;
    }
    else
    {
        current_element += c;
    }
}

template<>
inline void JsLexer::state_func<JsLexer::States::MULTI_LINE_COMMENT_MAYFINISH>(const SourceCharacter c, SourceReader& source)
{
    if ( c == '/' )
    {
        std::cout << "Multiline comment[[[" << current_element << "]]] To SPACE\n";
        state = States::UNDECIDED_STATE;
    }
    else if ( SourceCharacterTraits::isLineTerminator(c) )
    {
        current_element += "*\n";
        state = States::MULTI_LINE_COMMENT_NEWLINE;
    }
    else
    {
        current_element += '*';
        current_element += c;
        state = States::MULTI_LINE_COMMENT;
    }
}

template<>
inline void JsLexer::state_func<JsLexer::States::MULTI_LINE_COMMENT_NEWLINE>(const SourceCharacter c, SourceReader& source)
{
    if ( c == '*' )
    {
        state = States::MULTI_LINE_COMMENT_NEWLINE_MAYFINISH;
    }
    else
    {
        current_element += c;
    }
}

template<>
inline void JsLexer::state_func<JsLexer::States::MULTI_LINE_COMMENT_NEWLINE_MAYFINISH>(const SourceCharacter c, SourceReader& source)
{
    if ( c == '/' )
    {
        std::cout << "Multiline comment[[[" << current_element << "]]] To LF\n";
        state = States::UNDECIDED_STATE;
    }
    else
    {
        current_element += '*';
        current_element += c;
        state = States::MULTI_LINE_COMMENT_NEWLINE;
    }
}

template<>
inline void JsLexer::state_func<JsLexer::States::SINGLE_LINE_COMMENT>(const SourceCharacter c, SourceReader& source)
{
    if ( SourceCharacterTraits::isLineTerminator(c) )
    {
        std::cout << "Single line comment[[[" << current_element << "]]] To LF\n";
        state = States::UNDECIDED_STATE;
    }
    else
    {
        current_element += c;
    }
}

void JsLexer::parseChunk(SourceReader& source)
{
    line_num++;
    SourceCharacter c;
    while ( source.hasMore() && state != States::ERROR )
    {
        c = source.readNext();
        switch ( state )
        {
            case States::UNDECIDED_STATE: state_func<States::UNDECIDED_STATE>(c, source); break;
            case States::OPDIV: state_func<States::OPDIV>(c, source); break;
            case States::MULTI_LINE_COMMENT: state_func<States::MULTI_LINE_COMMENT>(c, source); break;
            case States::MULTI_LINE_COMMENT_MAYFINISH: state_func<States::MULTI_LINE_COMMENT_MAYFINISH>(c, source); break;
            case States::MULTI_LINE_COMMENT_NEWLINE: state_func<States::MULTI_LINE_COMMENT_NEWLINE>(c, source); break;
            case States::MULTI_LINE_COMMENT_NEWLINE_MAYFINISH: state_func<States::MULTI_LINE_COMMENT_NEWLINE_MAYFINISH>(c, source); break;
            case States::SINGLE_LINE_COMMENT: state_func<States::SINGLE_LINE_COMMENT>(c, source); break;
        }
    }
    
    
}
