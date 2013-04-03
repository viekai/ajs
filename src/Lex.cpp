/*
 * =====================================================================================
 *
 *       Filename:  Lex.cpp
 *
 *    Description:  ajs lexical analysis 
 *
 *        Version:  1.0
 *        Created:  03/12/2013 07:07:20 PM
 *       Revision:  none
 *
 *         Author:  YOUR NAME (tiny), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "Lex.h"

namespace AJS
{

enum CharacterType {
    TypeIdentifier,
    TypeZero,
    TypeNumber,

    TypeInvalid,
    TypeLineTerminator,
    TypeExclamationMark,
    TypeOpenParen,
    TypeCloseParen,
    TypeOpenBracket,
    TypeCloseBracket,
    TypeComma,
    TypeColon,
    TypeQuestion,
    TypeTilde,
    TypeQuote,
    TypeDot,
    TypeSlash,
    TypeBackSlash,
    TypeSemicolon,
    TypeOpenBrace,
    TypeCloseBrace,

    TypeAdd,
    TypeSub,
    TypeMultiply,
    TypeModulo,
    TypeAnd,
    TypeXor,
    TypeOr,
    TypeLess,
    TypeGreater,
    TypeEqual,

    TypeWhiteSpace,
};

static const unsigned short typesOfASCIICharacters[128] = {
/*   0 - Null               */ TypeInvalid,
/*   1 - Start of Heading   */ TypeInvalid,
/*   2 - Start of Text      */ TypeInvalid,
/*   3 - End of Text        */ TypeInvalid,
/*   4 - End of Transm.     */ TypeInvalid,
/*   5 - Enquiry            */ TypeInvalid,
/*   6 - Acknowledgment     */ TypeInvalid,
/*   7 - Bell               */ TypeInvalid,
/*   8 - Back Space         */ TypeInvalid,
/*   9 - Horizontal Tab     */ TypeWhiteSpace,
/*  10 - Line Feed          */ TypeLineTerminator,
/*  11 - Vertical Tab       */ TypeWhiteSpace,
/*  12 - Form Feed          */ TypeWhiteSpace,
/*  13 - Carriage Return    */ TypeLineTerminator,
/*  14 - Shift Out          */ TypeInvalid,
/*  15 - Shift In           */ TypeInvalid,
/*  16 - Data Line Escape   */ TypeInvalid,
/*  17 - Device Control 1   */ TypeInvalid,
/*  18 - Device Control 2   */ TypeInvalid,
/*  19 - Device Control 3   */ TypeInvalid,
/*  20 - Device Control 4   */ TypeInvalid,
/*  21 - Negative Ack.      */ TypeInvalid,
/*  22 - Synchronous Idle   */ TypeInvalid,
/*  23 - End of Transmit    */ TypeInvalid,
/*  24 - Cancel             */ TypeInvalid,
/*  25 - End of Medium      */ TypeInvalid,
/*  26 - Substitute         */ TypeInvalid,
/*  27 - Escape             */ TypeInvalid,
/*  28 - File Separator     */ TypeInvalid,
/*  29 - Group Separator    */ TypeInvalid,
/*  30 - Record Separator   */ TypeInvalid,
/*  31 - Unit Separator     */ TypeInvalid,
/*  32 - Space              */ TypeWhiteSpace,
/*  33 - !                  */ TypeExclamationMark,
/*  34 - "                  */ TypeQuote,
/*  35 - #                  */ TypeInvalid,
/*  36 - $                  */ TypeIdentifier,
/*  37 - %                  */ TypeModulo,
/*  38 - &                  */ TypeAnd,
/*  39 - '                  */ TypeQuote,
/*  40 - (                  */ TypeOpenParen,
/*  41 - )                  */ TypeCloseParen,
/*  42 - *                  */ TypeMultiply,
/*  43 - +                  */ TypeAdd,
/*  44 - ,                  */ TypeComma,
/*  45 - -                  */ TypeSub,
/*  46 - .                  */ TypeDot,
/*  47 - /                  */ TypeSlash,
/*  48 - 0                  */ TypeZero,
/*  49 - 1                  */ TypeNumber,
/*  50 - 2                  */ TypeNumber,
/*  51 - 3                  */ TypeNumber,
/*  52 - 4                  */ TypeNumber,
/*  53 - 5                  */ TypeNumber,
/*  54 - 6                  */ TypeNumber,
/*  55 - 7                  */ TypeNumber,
/*  56 - 8                  */ TypeNumber,
/*  57 - 9                  */ TypeNumber,
/*  58 - :                  */ TypeColon,
/*  59 - ;                  */ TypeSemicolon,
/*  60 - <                  */ TypeLess,
/*  61 - =                  */ TypeEqual,
/*  62 - >                  */ TypeGreater,
/*  63 - ?                  */ TypeQuestion,
/*  64 - @                  */ TypeInvalid,
/*  65 - A                  */ TypeIdentifier,
/*  66 - B                  */ TypeIdentifier,
/*  67 - C                  */ TypeIdentifier,
/*  68 - D                  */ TypeIdentifier,
/*  69 - E                  */ TypeIdentifier,
/*  70 - F                  */ TypeIdentifier,
/*  71 - G                  */ TypeIdentifier,
/*  72 - H                  */ TypeIdentifier,
/*  73 - I                  */ TypeIdentifier,
/*  74 - J                  */ TypeIdentifier,
/*  75 - K                  */ TypeIdentifier,
/*  76 - L                  */ TypeIdentifier,
/*  77 - M                  */ TypeIdentifier,
/*  78 - N                  */ TypeIdentifier,
/*  79 - O                  */ TypeIdentifier,
/*  80 - P                  */ TypeIdentifier,
/*  81 - Q                  */ TypeIdentifier,
/*  82 - R                  */ TypeIdentifier,
/*  83 - S                  */ TypeIdentifier,
/*  84 - T                  */ TypeIdentifier,
/*  85 - U                  */ TypeIdentifier,
/*  86 - V                  */ TypeIdentifier,
/*  87 - W                  */ TypeIdentifier,
/*  88 - X                  */ TypeIdentifier,
/*  89 - Y                  */ TypeIdentifier,
/*  90 - Z                  */ TypeIdentifier,
/*  91 - [                  */ TypeOpenBracket,
/*  92 - \                  */ TypeBackSlash,
/*  93 - ]                  */ TypeCloseBracket,
/*  94 - ^                  */ TypeXor,
/*  95 - _                  */ TypeIdentifier,
/*  96 - `                  */ TypeInvalid,
/*  97 - a                  */ TypeIdentifier,
/*  98 - b                  */ TypeIdentifier,
/*  99 - c                  */ TypeIdentifier,
/* 100 - d                  */ TypeIdentifier,
/* 101 - e                  */ TypeIdentifier,
/* 102 - f                  */ TypeIdentifier,
/* 103 - g                  */ TypeIdentifier,
/* 104 - h                  */ TypeIdentifier,
/* 105 - i                  */ TypeIdentifier,
/* 106 - j                  */ TypeIdentifier,
/* 107 - k                  */ TypeIdentifier,
/* 108 - l                  */ TypeIdentifier,
/* 109 - m                  */ TypeIdentifier,
/* 110 - n                  */ TypeIdentifier,
/* 111 - o                  */ TypeIdentifier,
/* 112 - p                  */ TypeIdentifier,
/* 113 - q                  */ TypeIdentifier,
/* 114 - r                  */ TypeIdentifier,
/* 115 - s                  */ TypeIdentifier,
/* 116 - t                  */ TypeIdentifier,
/* 117 - u                  */ TypeIdentifier,
/* 118 - v                  */ TypeIdentifier,
/* 119 - w                  */ TypeIdentifier,
/* 120 - x                  */ TypeIdentifier,
/* 121 - y                  */ TypeIdentifier,
/* 122 - z                  */ TypeIdentifier,
/* 123 - {                  */ TypeOpenBrace,
/* 124 - |                  */ TypeOr,
/* 125 - }                  */ TypeCloseBrace,
/* 126 - ~                  */ TypeTilde,
/* 127 - Delete             */ TypeInvalid,
};

void Lex::shift1()
{
    m_current = m_next1;
    m_next1 = m_next2;
    m_next2 = m_next3;
    if (LIKELY(m_buffer < m_bufferEnd))
        m_next3 = m_buffer[0];
    else
        m_next3 = -1;

    ++m_buffer;
}

void Lex::shift2()
{
    m_current = m_next2;
    m_next1 = m_next3;
    if (LIKELY(m_buffer + 1 < m_bufferEnd)) {
        m_next2 = m_buffer[0];
        m_next3 = m_buffer[1];
    } else {
        m_next2 = m_buffer < m_bufferEnd ? m_buffer[0] : -1;
        m_next3 = -1;
    }

    m_buffer += 2;
}

void Lex::shift3()
{
    m_current = m_next3;
    if (LIKELY(m_buffer + 2 < m_bufferEnd)) {
        m_next1 = m_buffer[0];
        m_next2 = m_buffer[1];
        m_next3 = m_buffer[2];
    } else {
        m_next1 = m_buffer < m_bufferEnd ? m_buffer[0] : -1;
        m_next2 = m_buffer + 1 < m_bufferEnd ? m_buffer[1] : -1;
        m_next3 = -1;
    }

    m_buffer += 3;
}

void Lex::shift4()
{
    if (LIKELY(m_buffer + 3 < m_bufferEnd)) {
        m_current = m_buffer[0];
        m_next1 = m_buffer[1];
        m_next2 = m_buffer[2];
        m_next3 = m_buffer[3];
    } else {
        m_current = m_buffer < m_bufferEnd ? m_buffer[0] : -1;
        m_next1 = m_buffer + 1 < m_bufferEnd ? m_buffer[1] : -1;
        m_next2 = m_buffer + 2 < m_bufferEnd ? m_buffer[2] : -1;
        m_next3 = -1;
    }

    m_buffer += 4;
}

void Lex::shiftLine()
{
    ASSERT(isLineTerminator(m_current));
    // Allow both CRLF and LFCR.
    if (m_current + m_next1 == '\n' + '\r')
        shift2();
    else
        shift1();
    
    ++m_lineNumber;
}

void Lex::parse()
{
    
}    

static bool isIdentifier(int ch)
{
    ASSERT(isASCII(ch));
    return (typesOfASCIICharacters[ch] <= TypeNumber);
}

Identifier* Lex::makeIdentifier(char* identifierStart, uint32_t identifierLength)
{
	return NULL;
}

void Lex::parseIdentifier()
{
    char* identifierStart = m_buffer;

    while(isIdentifier(m_current))
        shift1();

    uint32_t identifierLength = m_buffer - identifierStart;

    Identifier* ident = makeIdentifier(identifierStart, identifierLength);
}

void Lex::parseToken()
{
    while(isWhiteSpace(m_current))
        shift1();
    
    printf("%c", m_current);  
    shift1();
    if(UNLIKELY(m_current == -1))
        return;
    ASSERT(isASCII(m_current));

    CharacterType type =  static_cast<CharacterType>(typesOfASCIICharacters[m_current]);

    switch(type)
    {
        case TypeIdentifier:
            break;
		case TypeZero:
            break;
		case TypeNumber:
            break;
		case TypeInvalid:
            break;
		case TypeLineTerminator:
            break;
		case TypeExclamationMark:
            break;
		case TypeOpenParen:
            break;
		case TypeCloseParen:
            break;
		case TypeOpenBracket:
            break;
		case TypeCloseBracket:
            break;
		case TypeComma:
            break;
		case TypeColon:
            break;
		case TypeQuestion:
            break;
		case TypeTilde:
            break;
		case TypeQuote:
            break;
		case TypeDot:
            break;
		case TypeSlash:
            break;
		case TypeBackSlash:
            break;
		case TypeSemicolon:
            break;
		case TypeOpenBrace:
            break;
		case TypeCloseBrace:
            break;
		case TypeAdd:
            break;
		case TypeSub:
            break;
		case TypeMultiply:
            break;
		case TypeModulo:
            break;
		case TypeAnd:
            break;
		case TypeXor:
            break;
		case TypeOr:
            break;
		case TypeLess:
            break;
		case TypeGreater:
            break;
		case TypeEqual:
            break;
		case TypeWhiteSpace:
			break;
    }
}

}
