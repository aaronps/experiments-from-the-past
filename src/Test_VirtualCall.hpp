/* 
 * File:   Test_VirtualCall.hpp
 * Author: krom
 *
 * Created on October 30, 2012, 7:25 PM
 */

#ifndef TEST_VIRTUALCALL_HPP
#define	TEST_VIRTUALCALL_HPP

#include "Test.hpp"
#include "virtualcall.hpp"
#include "A.hpp"
#include <iostream>

using namespace std;

class Test_VirtualCall : public Test
{
public:
    Test_VirtualCall(long c) : Test(c) {}
    
    void runTest()
    {
        cout << "Test VirtualCall" << endl;

        TestSingleVirtualCall t;

        t.connect(&a);

        TimeMS start = getNow();

        uint32_t counter = repeat_count;
        do
        {
            t.test();
        } while ( --counter );

        TimeMS dif = getNow() - start;

        cout << "VirtualCall Time is " << dif << endl;

        a.msg_from_a();
    }
    
};

#endif	/* TEST_VIRTUALCALL_HPP */

