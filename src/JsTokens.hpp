/* 
 * File:   JsTokens.hpp
 * Author: krom
 *
 * Created on November 27, 2012, 7:59 AM
 */

#ifndef JSTOKENS_HPP
#define	JSTOKENS_HPP

#include <string>

struct TokenID
{
    enum TYPE
    {
        WhiteSpace,
        LineTerminator,
        Comment,
        Token,
        
            IdentifierName,
                ReservedWord,
                Keyword,
                FutureReservedWord,
                StrictFutureReservedWord,
                NullLiteral,
                BooleanLiteral,
                
            Punctuator,
            
            NumericLiteral,
            
            StringLiteral,
    };
};

class Token
{
    TokenID::TYPE type;
    int line;
    int column;
    std::string value;
public:
    Token(TokenID::TYPE type, int line, int column, const std::string& value)
        : type(type), line(line), column(column), value(value) {}
};

class JsTokens
{
    
public:
    JsTokens(){}
    
    
};

#endif	/* JSTOKENS_HPP */

