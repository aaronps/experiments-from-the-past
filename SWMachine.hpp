/* 
 * File:   SWMachine.hpp
 * Author: krom
 *
 * Created on November 19, 2012, 8:38 PM
 */

#ifndef SWMACHINE_HPP
#define	SWMACHINE_HPP

struct TStatesSW
{
    typedef enum { A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, END } values;
};

class SWMachine
{
private:
    TStatesSW::values state;
    
public:
    SWMachine() :state(TStatesSW::A){}
    
    void run();
};

#endif	/* SWMACHINE_HPP */

