/* 
 * File:   main.cpp
 * Author: krom
 *
 * Created on November 23, 2010, 12:59 AM
 */


#define TEST_SFSIGSLOT
#define TEST_VIRTUALCALL
//#define TEST_BOOST
#define TEST_FASTDELEGATE
//#define TEST_CUSTOMCALLABLE
//#define TEST_SIGNALDELEGATE

#include <iostream>
#include <list>

#include <time.h>
#include <sys/time.h>
#include <cerrno>
#include <stdint.h>
#include <string.h>

#include "Test.hpp"

#include "A.hpp"
#include "B.hpp"


#ifdef TEST_SFSIGSLOT
    #include "Test_SFSignal.hpp"
#endif

#ifdef TEST_VIRTUALCALL
    #include "Test_VirtualCall.hpp"
#endif

#ifdef TEST_BOOST
    #include "Test_Boost.hpp"
#endif

#ifdef TEST_FASTDELEGATE
    #include "Test_FastDelegate.hpp"
#endif

#ifdef TEST_CUSTOMCALLABLE
    #include "customcallable.hpp"
#endif



#ifdef TEST_SIGNALDELEGATE
    #include "Signal.hpp"
#endif


using namespace std;


A a;
B b;
TimeMS start;
TimeMS dif;
int counter;


void heating()
{
    cout << "Heating..." << endl;

    int degrees=0;

    for ( counter = 10000000; counter; --counter )
    {
        degrees++;
    }

    cout << "...degrees " << degrees << endl;
}

time_t get_start_second()
{
    time_t n;
    time_t last = time(0);
    do
    {
        n = time(0);
    } while ( n == last );
    return n;
}

#ifdef TEST_CUSTOMCALLABLE
void test_customcallable()
{
    cout << "Custom Callable" << endl;

    CustomCallableSignal css;

    css.connect<A,&A::dec>(&a);
    css.connect<B,&B::inc_me>(&b);

    start = get_start_second();

    for ( counter = ITERATIONS; counter; --counter )
    {
        css.raise();
    }

    dif = time(0) - start;

    cout << "CustomCallableSignal Time is " << dif << endl;

    a.msg_from_a();
    b.msg_from_b();
}
#else
    #define test_customcallable()
#endif

#ifdef TEST_SIGNALDELEGATE
void test_signaldelegate()
{
    cout << "Gallant::Signal" << endl;

    Gallant::Signal0<void> gs;

    gs.Connect(&a, &A::dec);
    gs.Connect(&b, &B::inc_me);

    start = get_start_second();

    for ( counter = ITERATIONS; counter; --counter )
    {
        gs();
    }

    dif = time(0) - start;

    cout << "Gallant::signal Time is " << dif << endl;

    a.msg_from_a();
    b.msg_from_b();
}
#else
    #define test_signaldelegate()
#endif

//#include <tr1/functional>

int main(int argc, char** argv)
{
    long count = 1000000000;
    heating();
    
    // store a call to a member function
//    std::tr1::function<void(A&)> callit = &A::dec;
//    callit(a);
    
    
#ifdef TEST_VIRTUALCALL
    {
        Test_VirtualCall test(count);
        test.runTest();
    }
#endif
    
#ifdef TEST_SFSIGSLOT
    {
        Test_SFSignal test(count);
        test.runTest();
    }
#endif
    
#ifdef TEST_BOOST
    {
        Test_Boost test(count);
        test.runTest();
    }
#endif
    
#ifdef TEST_FASTDELEGATE
    {
        Test_FastDelegate test(count);
        test.runTest();
    }
#endif
    

    test_customcallable();

    test_signaldelegate();
    
    return 0;


}

