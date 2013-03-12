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

using namespace std;

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        cout << "usage: ajs filename" << endl;
        return 1;
    }

    cout << "----------------------------------" << endl;    
    cout << "this is a javascript vm for fun" << endl;
    cout << "----------------------------------"<< endl;

    AJS::CodeStream codeStream;

    codeStream.readFile(argv[1]);

    return 0;
}
