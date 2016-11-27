/* 
 * File:   B.hpp
 * Author: krom
 *
 * Created on October 30, 2012, 7:15 PM
 */

#ifndef B_HPP
#define	B_HPP

#include <iostream>
using namespace std;

#ifdef TEST_VIRTUALCALL
#include "virtualcall.hpp"
class B : public EventListener
#else
class B
#endif
{
private:
    int f;
public:
    B() : f(0) {}
    void msg_from_b()
    {
        cout << "BBB: " << f << endl;
    }
    void recv_message(const char * str)
    {
        cout << "B: " << str << '[' << f << ']' <<  endl;
    }
    void inc_me() { f+=1; }
    void dec_me() { f-=1; }
#ifdef TEST_VIRTUALCALL
    virtual void onEvent(const int n) { f+=n; }
#endif
};

extern B b;

#endif	/* B_HPP */

