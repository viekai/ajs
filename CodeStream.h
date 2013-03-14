/*
 * =====================================================================================
 *
 *       Filename:  CodeStream.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/12/2013 07:33:05 PM
 *       Revision:  none
 *
 *         Author:  YOUR NAME (tiny), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <fstream>
#include <stdlib.h>

namespace AJS
{

class CodeStream
{

public:
    bool readFile(const char* fileName);
    ~CodeStream()
    {
       free(m_buffer); 
    }

private:
    CodeStream& operator=(const CodeStream& o);
    char* m_buffer;
    int   m_size;    

};

}
