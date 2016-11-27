/* 
 * File:   Test_SFSignal.hpp
 * Author: krom
 *
 * Created on October 30, 2012, 7:09 PM
 */

#ifndef TEST_SFSIGNAL_HPP
#define	TEST_SFSIGNAL_HPP

//#ifdef TEST_SFSIGSLOT

#include "Test.hpp"
#include "sfsigslot.hpp"
#include "A.hpp"
#include <iostream>

using namespace std;

class Test_SFSignal : public Test
{
public:
    Test_SFSignal(long c) : Test(c) {}
    
    void runTest()
    {
        cout << "Testing SFSignal" << endl;

        TestSFSignalData t;

        t.connect(&a,&A::addNum);

        TimeMS start = getNow();

        uint32_t counter = repeat_count;
        do
        {
            t.test();
        } while ( --counter );

        TimeMS dif = getNow() - start;

        cout << "SFSignal Time is " << dif << endl;
        a.msg_from_a();
    }
    
};

//#endif

#endif	/* TEST_SFSIGNAL_HPP */

