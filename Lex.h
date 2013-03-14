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
namespace AJS
{
//----------------------------------------

class CodeStream;

//----------------------------------------
class Lex
{
public:
    Lex(CodeStream &code) : m_code(code)
    {
    };

    void parse();
private:
    CodeStream &m_code;
};
    
}

