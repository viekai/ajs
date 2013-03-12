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

namespace AJS
{

class CodeStream
{

public:
    bool readFile(const char* fileName);

private:
    char* m_buffer;
    
};

}
