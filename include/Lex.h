/*
 * =====================================================================================
 *
 *       Filename:  Lex.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/12/2013 07:09:15 PM
 *       Revision:  none
 *
 *         Author:  YOUR NAME (tiny), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "AJS.h"
#include "AsciicType.h"

namespace AJS
{
//----------------------------------------
enum JSTokenType
{
	NULLTOKEN = 1,
	TRUETOKEN,
	FALSETOKEN,

	BREAK,
	CASE,
	CATCH,
	CONSTTOKEN,
	DEFAULT,
	FINALLY,
	FOR,
	INSTANCEOF,
	NEW,
	VAR,
	CONTINUE,
	FUNCTION,
	RETURN,
	VOIDTOKEN,
	DELETETOKEN,
	IF,
	THISTOKEN,
	DO,
	WHILE,
	ELSE,
	INTOKEN,
	SWITCH,
	THROW,
	TRY,
	YPEOF,
	WITH,
	DEBUGGER,
};

struct JSTokenData
{
    int intValue;
    double doubleVale;
};

struct JSTokenInfo
{
    int line;
    int startOffset;
    int endOffset;
};

struct JSToken
{
    JSTokenType type;
    JSTokenData data;
    JSTokenInfo info;
};

class Identifier
{

};

//----------------------------------------
class Lex
{
public:
    Lex(char* buffer, int size) : m_buffer(buffer), m_size(size)
    {
        m_bufferEnd = buffer + size;
        shift4();
    };

    void parse();
private:

    char* m_buffer;
    int   m_size;    
    char* m_bufferEnd;

    int m_current;
    int m_next1;
    int m_next2;
    int m_next3;

    int m_lineNumber;

    void shift1();
    void shift2();
    void shift3();
    void shift4();

    void shiftLine();

    void parseToken();

	void parseIdentifier();

	Identifier* makeIdentifier(char* identifierStart, uint32_t identifierLength);

    inline bool isLineTerminator(int ch)
    {
        return ch == '\r' || ch == '\n' || (ch & ~1) == 0x2028;
    }

    inline bool isWhiteSpace(int ch)
    {
        ASSERT(isASCII(ch));
        return (ch == ' ' || ch == '\t' || ch == 0xB || ch == 0xC);
    }

};


    
}

