/* 
 * File:   Test.hpp
 * Author: krom
 *
 * Created on October 30, 2012, 7:10 PM
 */

#ifndef TEST_HPP
#define	TEST_HPP

#include <time.h>
#include <sys/time.h>
#include <cerrno>
#include <stdint.h>
#include <string.h>

#include <iostream>

typedef uint32_t TimeMS;

class Test
{
protected:
    long repeat_count;
    
public:
    Test(long repeat_count) : repeat_count(repeat_count){}
    virtual ~Test(){}
    
    virtual void runTest() = 0;
    
    TimeMS getNow()
    {
            struct timeval t;

            if ( gettimeofday(&t,0) )
            {
                    std::cout << "Error getting time" << strerror(errno) << std::endl;
            }

            return (t.tv_sec * 1000) + (t.tv_usec/1000);
    }
    
};

#endif	/* TEST_HPP */

