/*
 * =====================================================================================
 *
 *       Filename:  AJS.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/12/2013 07:09:45 PM
 *       Revision:  none
 *
 *         Author:  YOUR NAME (tiny), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <iostream>
#include <string>
#include "CodeStream.h"
#include "Lex.h"

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        std::cout << "usage: ajs filename" << std::endl;
        return 1;
    }

    std::cout << "----------------------------------" << std::endl;    
    std::cout << "this is a javascript vm for fun" << std::endl;
    std::cout << "----------------------------------"<< std::endl;

    AJS::CodeStream codeStream;

    if(!codeStream.readFile(argv[1]))
    {
        return 1;
    }

        
    AJS::Lex lex(codeStream);
    lex.parse();

    return 0;
}

