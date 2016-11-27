/* 
 * File:   A.hpp
 * Author: krom
 *
 * Created on October 30, 2012, 7:13 PM
 */

#ifndef A_HPP
#define	A_HPP

#include <iostream>
using namespace std;

#ifdef TEST_VIRTUALCALL
#include "virtualcall.hpp"
class A : public EventListener
#else
class A
#endif
{
private:
    long v;
public:
    A() : v(0) {}
    void on_message(const char * str)
    {
        cout << "A: " << str << '[' << v << ']' << endl;
    }

    void msg_from_a()
    {
        cout << "AAA: " << v << endl;
    }
    void inc() { v+=1; }
    void dec() { v-=1; }
    
    void addNum(const int n) { v += n;}

#ifdef TEST_VIRTUALCALL
    virtual void onEvent(const int n) { v+=n; }
#endif
};

extern A a;

#endif	/* A_HPP */

