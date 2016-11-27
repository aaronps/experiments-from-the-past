/* 
 * File:   Test_Boost.hpp
 * Author: krom
 *
 * Created on October 30, 2012, 7:33 PM
 */

#ifndef TEST_BOOST_HPP
#define	TEST_BOOST_HPP

#include "Test.hpp"
#include <boost/signal.hpp>
#include <boost/bind.hpp>
#include "A.hpp"
#include <iostream>

using namespace std;

class BoostSignalHolder
{
public:
    boost::signal0<void> signal;
    
    void test();
};

class Test_Boost : public Test
{
public:
    Test_Boost(long c) : Test(c) {}
    
    void runTest()
    {
        cout << "Test Boost::signal" << endl;
        
        BoostSignalHolder bsh;
        
        bsh.signal.connect(boost::bind(&A::inc, &a));

        TimeMS start = getNow();

        uint32_t counter = repeat_count;
        do
        {
            bsh.test();
        } while ( --counter );

        TimeMS dif = getNow() - start;

        cout << "Boost::signal Time is " << dif << endl;

        a.msg_from_a();
    }
    
};

#endif	/* TEST_BOOST_HPP */

