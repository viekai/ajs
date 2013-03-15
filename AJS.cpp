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
#include <fstream>
#include <stdlib.h>

#include "Lex.h"
#include "AJS.h"

bool readFile(const char* fileName, char** buffer, int* size)
{
    std::ifstream fin;
    fin.open(fileName, std::ifstream::in);

    if(!fin)
        return false;

    fin.seekg(0, fin.end);
    int length = fin.tellg();
    fin.seekg(0, fin.beg);

    *size = length;
    *buffer = (char*)malloc(length);

    fin.get(*buffer, length);
#if DEBUG
    std::cout << *buffer << std::endl;
#endif
    fin.close();
}

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
    
	int size;
	char* buffer;
	readFile(argv[1], &buffer, &size);

    AJS::Lex lex(buffer, size);
    lex.parse();

    return 0;
}

