/*
 * =====================================================================================
 *
 *       Filename:  AJS.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/12/2013 07:10:44 PM
 *       Revision:  none
 *
 *         Author:  YOUR NAME (tiny), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define ASSERT(x) \
    do{\
        if(!(x)){\
            printf("ASSERT FAILED (%s:%d): %s", __FILE__, __LINE__, #x);\
            *(int*)0x0=0xdeaddaad;\
            }\
    }while(0)


#ifndef UNLIKELY
#define UNLIKELY(x) __builtin_expect((x), 0)
#endif

#ifndef LIKELY
#define LIKELY(x) __builtin_expect((x), 1)
#endif
