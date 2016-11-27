/* 
 * File:   Test_FastDelegate.hpp
 * Author: krom
 *
 * Created on October 30, 2012, 7:52 PM
 */

#ifndef TEST_FASTDELEGATE_HPP
#define	TEST_FASTDELEGATE_HPP

#include "Test.hpp"
#include "FastDelegate.h"
#include "A.hpp"
#include <iostream>

using namespace std;

class FastDelegateSignalHolder
{
public:
    fastdelegate::FastDelegate1<int> signal;
    
    void test();
};

class Test_FastDelegate : public Test
{
public:
    Test_FastDelegate(long c) : Test(c) {}
    
    void runTest()
    {
        cout << "Test FastDelegate" << endl;
        
        FastDelegateSignalHolder bsh;
        
        bsh.signal = fastdelegate::FastDelegate1<int>(&a, &A::addNum);

        TimeMS start = getNow();

        uint32_t counter = repeat_count;
        do
        {
            bsh.test();
        } while ( --counter );

        TimeMS dif = getNow() - start;

        cout << "FastDelegate Time is " << dif << endl;

        a.msg_from_a();
    }
    
};

#endif	/* TEST_FASTDELEGATE_HPP */

