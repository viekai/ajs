/*
 * =====================================================================================
 *
 *       Filename:  CodeStream.cpp
 *
 *    Description:  for  
 *
 *        Version:  1.0
 *        Created:  03/12/2013 07:31:55 PM
 *       Revision:  none
 *
 *         Author:  YOUR NAME (tiny), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <iostream>
#include <fstream>
#include "CodeStream.h"
#include <stdlib.h>

namespace AJS
{
    bool CodeStream::readFile(const char* fileName)
    {
        std::ifstream fin;
        fin.open(fileName, std::ifstream::in);

        if(!fin)
            return false;

        fin.seekg(0, fin.end);
        int length = fin.tellg();
        fin.seekg(0, fin.beg);

        m_buffer = (char*)malloc(length);

        fin.get(m_buffer, length);
#if DEBUG
        std::cout << m_buffer << std::endl;
#endif
        fin.close();
    }
     
}
