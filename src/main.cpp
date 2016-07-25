/* 
 * File:   main.cpp
 * Author: krom
 *
 * Created on March 8, 2012, 9:35 PM
 */

#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>
#include <list>

#include "SourceReader.hpp"
#include "JsLexer.hpp"

const char *keywords[] = 
{
    "break",    "case",         "catch",        "continue",     "debugger",
    "default",  "delete",       "do",           "else",         "finally",
    "for",      "function",     "if",           "in",           "instanceof",
    "new",      "return",       "switch",       "this",         "throw",
    "try",      "typeof",       "var",          "void",         "while",
    "with"
};

#define KEYWORDS_LEN (sizeof(keywords)/sizeof(const char *))

const char *future_reserved[] =
{
    "class",    "enum",         "extends",      "super",        "const",
    "export",   "import"
};

#define FUTURE_RESERVED_LEN (sizeof(future_reserved)/sizeof(const char *))

const char *future_reserved_strict[] =
{
    "implements","interface",   "let",          "package",      "private",
    "protected", "public",      "static",       "yeld"
};

#define FUTURE_RESERVED_STRICT_LEN (sizeof(future_reserved_strict)/sizeof(const char *))

bool isReservedWord( const std::string& s)
{
    int n;
    for ( n = 0 ; n < KEYWORDS_LEN; n++)
    {
        if ( !s.compare(keywords[n]) )
        {
            return true;
        }
    }
    
    for ( n = 0 ; n < FUTURE_RESERVED_LEN; n++)
    {
        if ( !s.compare(future_reserved[n]) )
        {
            return true;
        }
    }
    
    for ( n = 0 ; n < FUTURE_RESERVED_STRICT_LEN; n++)
    {
        if ( !s.compare(future_reserved_strict[n]) )
        {
            return true;
        }
    }
    
    return false;
}

// 7.1 format control characters
bool isFormatControl( int c )
{
    return c == 0x200c || c == 0x200d;
}

// 7.2 White Space
// Still missing: "any other unicode category Z?"
bool isWhitespace( int c )
{
    switch ( c )
    {
        case 0x09: // tab
        case 0x0b: // vertial tab
        case 0x0c: // form feed
        case 0x20: // space
        case 0xa0: // no break space
        case 0xfeff: // BOM
            return true;
    }
    return false;
}

// 7.3 Line Terminators
// Still missing: cr+lf = only one line terminator
bool isLineTerminator( int c )
{
    switch ( c )
    {
        case 0x0a: // lf
        case 0x0d: // cr
        case 0x2028: // line separator
        case 0x2029: // paragraph separator
            return true;
    }
    return false;
}

// 7.4 Comments: done

// 7.6 Identifier names
// Missing: escape sequences

bool isUnicodeLetter( int c )
{
    return isalpha(c);
}

bool isIdentifierStart( int c )
{
    return isUnicodeLetter(c) || c == '$' || c == '_';
}

bool isUnicodeDigit(int c)
{
    return isdigit(c);
}

// missing: UnicodeCombiningMark, UnicodeConnectorPuntuation
bool isIdentifierPart( int c )
{
    return isIdentifierStart(c) || isUnicodeDigit(c) || isFormatControl(c);
}

class Token
{
public:
    enum
    {
        IDENTIFIER,
        RESERVEDWORD,
        NUMBER,
        STRING,
        TNULL,
        TTRUE,
        TFALSE
    };
    int type;
    std::string text;
    Token(int type, std::string& text) : type(type), text(text) {}
    Token(int type) : type(type) {}
    
    friend std::ostream & operator << (std::ostream &out, const Token& token);
};

std::ostream & operator << (std::ostream &out, const Token& token)
{
    switch ( token.type )
    {
        case Token::IDENTIFIER: out << "Identifier:<" << token.text << ">\n"; break;
        case Token::RESERVEDWORD: out << "Reserved Word:<" << token.text << ">\n"; break;
        case Token::TNULL: out << "Null:\n"; break;
        case Token::TTRUE: out << "True:\n"; break;
        case Token::TFALSE: out<< "False:\n"; break;
        default:
            out << "!!UNKNOWN!!\n";
    }
    return out;
}

class Parser
{
private:
    std::list<Token> tokens;
    enum {
        ST_SKIPPING_SPACE = 0,
        ST_IDENTIFIER,
        ST_NUMBER,
        ST_DOUBLESTRING,
        ST_DOUBLESTRINGESCAPE,
        ST_SINGLESTRING,
        ST_SINGLESTRINGESCAPE,
        ST_OPPLUS,
        ST_OPMINUS,
        ST_OPMUL,
        ST_OPDIV,
        ST_OPOR,
        ST_OPNOT,
        ST_OPNOTEQ,
        ST_OPLESS,
        ST_OPGREAT,
        ST_OPAND,
        ST_OPQUESTION,
        ST_COMMENT,
        ST_REGEX,
        ST_MLINECOMMENT,
        ST_MLINECOMMENT2LF,
        ST_MLINECOMMENTALMOST,
        ST_MLINECOMMENTALMOST2LF,
        
        ST_ERROR
    } state;
    
    int linenum;
public:
    Parser() : state(ST_SKIPPING_SPACE), linenum(0) {}
    
    bool parseChunk( std::string& chunk )
    {
        std::string::iterator iter = chunk.begin();
        std::string::iterator end = chunk.end();
        
        std::string curt;
        linenum++;
        int c;
        bool repeat = false;
        
        outout:while ( iter != end && state != ST_ERROR)
        {
            c = *iter;
            do
            {
                repeat = false;
            
                switch ( state )
                {
                    case ST_SKIPPING_SPACE:
                        if ( isWhitespace(c) ) break;
                        if ( isLineTerminator(c) ) break;
    //                    if ( isspace(c) ) break;
                        if ( isIdentifierStart(c) )
                        {
                            curt += c;
                            state = ST_IDENTIFIER;
                        }
                        else if ( isdigit(c) )
                        {
                            curt += c;
                            state = ST_NUMBER;
                        }
                        else switch ( c )
                        {
                            case '"':
                                state = ST_DOUBLESTRING;
                                break;
                            case '\'':
                                state = ST_SINGLESTRING;
                                break;
                            case '(':
                                std::cout << "Open:[(]\n";
                                break;
                            case ')':
                                std::cout << "Close:[)]\n";
                                break;
                            case '{':
                                std::cout << "Open:[{]\n";
                                break;
                            case '}':
                                std::cout << "Close:[}]\n";
                                break;
                            case '[':
                                std::cout << "Open:[[]\n";
                                break;
                            case ']':
                                std::cout << "Close:[]]\n";
                                break;
                            case ';':
                                std::cout << "EndOfStatement:[;]\n";
                                break;
                            case ':':
                                std::cout << "Colon:[:]\n";
                                break;
                            case '.':
                                std::cout << "Dot:[.]\n";
                                break;
                            case ',':
                                std::cout << "Coma:[,]\n";
                                break;
                            case '=':
                                std::cout << "Equal:[=]\n";
                                break;
                            case '+':
                                state = ST_OPPLUS;
                                break;
                            case '-':
                                state = ST_OPMINUS;
                                break;
                            case '*':
                                state = ST_OPMUL;
                                break;
                            case '/':
                                state = ST_OPDIV;
                                break;
                            case '|':
                                state = ST_OPOR;
                                break;
                            case '!':
                                state = ST_OPNOT;
                                break;
                            case '<':
                                state = ST_OPLESS;
                                break;
                            case '>':
                                state = ST_OPGREAT;
                                break;
                            case '&':
                                state = ST_OPAND;
                                break;
                            case '?':
                                std::cout << "Operator:[?]\n";
                                break;
                            default:
                                std::cout << "Error at line " << linenum
                                        << " character <" << (char)c << "> at " << (iter - chunk.begin()) + 1
                                        << " not recognized\n";
                                state = ST_ERROR;
                        }
                        break;

                    case ST_IDENTIFIER:
                        if ( isIdentifierPart(c) )
                        {
                            curt += c;
                        }
                        else
                        {
                            if ( isReservedWord(curt) )
                            {
                                tokens.push_back(Token(Token::RESERVEDWORD, curt));
                            }
                            else if ( curt == "null" )
                            {
                                tokens.push_back(Token(Token::TNULL, curt));
                            }
                            else if ( curt == "true" )
                            {
                                tokens.push_back(Token(Token::TTRUE, curt));
                            }
                            else if ( curt == "false" )
                            {
                                tokens.push_back(Token(Token::TFALSE, curt));
                            }
                            else
                            {    
                                    tokens.push_back(Token(Token::IDENTIFIER, curt));
                            }
                        
                            state = ST_SKIPPING_SPACE;
                            repeat = true;
                            curt = "";
                        }
                        break;

                    case ST_NUMBER:
                        if ( isdigit(c) )
                        {
                            curt += c;
                        }
                        else
                        {
                            std::cout << "Number:[" << curt << "]\n";
                            state = ST_SKIPPING_SPACE;
                            repeat = true;
                            curt = "";
                        }
                        break;

                    case ST_DOUBLESTRING:
                        switch ( c )
                        {
                            case '"':
                                std::cout << "StringD:[" << curt << "]\n";
                                state = ST_SKIPPING_SPACE;
                                curt = "";
                                break;
                            case '\\':
                                state = ST_DOUBLESTRINGESCAPE;
                                break;
                            default:
                                curt += c;
                        }
                        break;

                    case ST_DOUBLESTRINGESCAPE:
                        curt += c;
                        state = ST_DOUBLESTRING;
                        break;

                    case ST_SINGLESTRING:
                        switch ( c )
                        {
                            case '\'':
                                std::cout << "StringS:[" << curt << "]\n";
                                state = ST_SKIPPING_SPACE;
                                curt = "";
                                break;
                            case '\\':
                                state = ST_SINGLESTRINGESCAPE;
                                break;
                            default:
                                curt += c;
                        }
                        break;

                    case ST_SINGLESTRINGESCAPE:
                        curt += c;
                        state = ST_SINGLESTRING;
                        break;

                    case ST_OPPLUS:
                        if ( c == '+' )
                        {
                            std::cout << "Operator:[++]\n";
                            state = ST_SKIPPING_SPACE;
                        }
                        else if ( c == '=' )
                        {
                            std::cout << "Operator:[+=]\n";
                            state = ST_SKIPPING_SPACE;
                        }
                        else
                        {
                            std::cout << "Operator:[+]\n";
                            state = ST_SKIPPING_SPACE;
                            repeat = true;
                        }
                        break;

                    case ST_OPMINUS:
                        if ( c == '-' )
                        {
                            std::cout << "Operator:[--]\n";
                            state = ST_SKIPPING_SPACE;
                        }
                        else if ( c == '=' )
                        {
                            std::cout << "Operator:[-=]\n";
                            state = ST_SKIPPING_SPACE;
                        }
                        else
                        {
                            std::cout << "Operator:[-]\n";
                            state = ST_SKIPPING_SPACE;
                            repeat = true;
                        }
                        break;

                    case ST_OPMUL:
                        if ( c == '=' )
                        {
                            std::cout << "Operator:[*=]\n";
                            state = ST_SKIPPING_SPACE;
                        }
                        else
                        {
                            std::cout << "Operator:[*]\n";
                            state = ST_SKIPPING_SPACE;
                            repeat = true;
                        }
                        break;

                    case ST_OPDIV:
                        if ( c == '=' )
                        {
                            std::cout << "Operator:[/=]\n";
                            state = ST_SKIPPING_SPACE;
                        }
                        else if ( c == '*' )
                        {
                            std::cout << "Multiline Comment";
                            state = ST_MLINECOMMENT;
                        }
                        else if ( c == '/' )
                        {
                            std::cout << "Single Line Comment";
                            state = ST_COMMENT;
                        }
                        else
                        {
                            std::cout << "Operator:[/]\n";
                            state = ST_SKIPPING_SPACE;
                            repeat = true;
                        }
                        break;

                    case ST_MLINECOMMENT:
                        if ( c == '*' )
                        {
                            state = ST_MLINECOMMENTALMOST;
                        }
                        else if ( isLineTerminator(c) )
                        {
                            state = ST_MLINECOMMENT2LF;
                        }
                        break;

                    case ST_MLINECOMMENTALMOST:
                        if ( c == '/' )
                        {
                            std::cout << "...to space\n";
                            state = ST_SKIPPING_SPACE;
                            c = ' ';
                            repeat = true;
                        }
                        else if ( isLineTerminator(c) )
                        {
                            state = ST_MLINECOMMENT2LF;
                        }
                        else
                        {
                            state = ST_MLINECOMMENT;
                        }
                        break;
                        
                    case ST_MLINECOMMENT2LF:
                        if ( c == '*' )
                        {
                            state = ST_MLINECOMMENTALMOST2LF;
                        }
                        break;

                    case ST_MLINECOMMENTALMOST2LF:
                        if ( c == '/' )
                        {
                            std::cout << "... to LF\n";
                            c = '\n';
                            state = ST_SKIPPING_SPACE;
                            repeat = true;
                        }
                        else
                        {
                            state = ST_MLINECOMMENT2LF;
                        }
                        break;

                    case ST_COMMENT:
                        if ( isLineTerminator(c) )
                        {
                            std::cout << "...ends to newline\n";
                            state = ST_SKIPPING_SPACE;
                            repeat = true;
                        }
                        break;

                    case ST_OPOR:
                        if ( c == '|' )
                        {
                            std::cout << "Operator:[||]\n";
                            state = ST_SKIPPING_SPACE;
                        }
                        else
                        {
                            std::cout << "Operator:[|]\n";
                            state = ST_SKIPPING_SPACE;
                            repeat = true;
                        }
                        break;

                    case ST_OPNOT:
                        if ( c == '=' )
                        {
                            state = ST_OPNOTEQ;
                        }
                        else
                        {
                            std::cout << "Operator:[!]\n";
                            state = ST_SKIPPING_SPACE;
                            repeat = true;
                        }
                        break;

                    case ST_OPNOTEQ:
                        if ( c == '=' )
                        {
                            std::cout << "Operator:[!==]\n";
                            state = ST_SKIPPING_SPACE;
                        }
                        else
                        {
                            std::cout << "Operator:[!=]\n";
                            state = ST_SKIPPING_SPACE;
                            repeat = true;
                        }
                        break;

                    case ST_OPLESS:
                        if ( c == '=' )
                        {
                            std::cout << "Operator:[<=]\n";
                            state = ST_SKIPPING_SPACE;
                        }
                        else
                        {
                            std::cout << "Operator:[<]\n";
                            state = ST_SKIPPING_SPACE;
                            repeat = true;
                        }
                        break;

                    case ST_OPGREAT:
                        if ( c == '=' )
                        {
                            std::cout << "Operator:[>=]\n";
                            state = ST_SKIPPING_SPACE;
                        }
                        else
                        {
                            std::cout << "Operator:[>]\n";
                            state = ST_SKIPPING_SPACE;
                            repeat = true;
                        }
                        break;

                    case ST_OPAND:
                        if ( c == '=' )
                        {
                            std::cout << "Operator:[&=]\n";
                            state = ST_SKIPPING_SPACE;
                        }
                        else if ( c == '&' )
                        {
                            std::cout << "Operator:[&&]\n";
                            state = ST_SKIPPING_SPACE;
                        }
                        else
                        {
                            std::cout << "Operator:[&]\n";
                            state = ST_SKIPPING_SPACE;
                            repeat = true;
                        }
                        break;
                }

            } while ( repeat && state != ST_ERROR);
            
            iter++;
        }
        
        return state == ST_ERROR;
    }
    
    void dump(std::ostream& out)
    {
        std::list<Token>::iterator i = tokens.begin();
        while ( i != tokens.end() )
        {
            out << *i;
            i++;
        }
    }
    
};


int main(int argc, char** argv)
{
    Parser parser;
    
    std::string line;
    
    std::ifstream file;
    file.open("test.js", std::ios::in | std::ios::binary | std::ios::ate );
    
    std::streamoff size = file.tellg();
    if ( size != -1 )
    {
        JsLexer lexer;

        file.seekg(0, std::ios::beg);
        
        uint8_t buffer[size];
        
        std::streamoff r = file.readsome(reinterpret_cast<char*>(buffer), size);

//        std::cout << r << "[[[" << (char *)buffer << "]]]" << (std::streamoff)size ;
        SourceReader source(buffer, size);
        lexer.parseChunk(source);
    }
        
    
    
    
//    while (std::getline(file, line))
//    {
////        std::cout << "line was[" << line << "]\n";
//        line += '\n';
//        if ( parser.parseChunk(line) ) 
//        {
//            std::cout << "Parser returned error\n";
//            break;
//        }
//    }
    
    
    
//    std::string top = "function test(name){ var x = 5, y={a:\"some text\",b:42}; }\n"
//            "a[b] = 1;\n"
//            "a.b = 4;";
    file.close();
//    sleep(1);

    parser.dump(std::cout);

    return 0;
}

