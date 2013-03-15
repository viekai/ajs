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

void Lex::parseToken()
{
    while(isWhiteSpace(m_current))
        shift1();
        
    printf("%c", m_current);  
    shift1();
    if(UNLIKELY(m_current == -1))
        return;
}

}
