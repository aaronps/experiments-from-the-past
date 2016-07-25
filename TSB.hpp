/* 
 * File:   TSB.hpp
 * Author: krom
 *
 * Created on November 19, 2012, 10:11 PM
 */

#ifndef TSB_HPP
#define	TSB_HPP

class TSB
{
private:
    typedef enum { A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, END } States;
    States state;
    
public:
    TSB() : state(A) {}
    
    void run();    
    
    template<States> void func();
};

#endif	/* TSB_HPP */

