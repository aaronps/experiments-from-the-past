/* 
 * File:   TS.hpp
 * Author: krom
 *
 * Created on November 19, 2012, 8:29 PM
 */

#ifndef TS_HPP
#define	TS_HPP

struct TStates
{
    typedef enum { A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, END } States;
};

struct null {};

template<bool> struct wrap{};

template<TStates::States start, TStates::States end, typename B = wrap<true> >
struct enum_iterator
{
    static const enum_iterator<TStates::States(start+1),end> next;
};

template<TStates::States start, TStates::States end>
struct enum_iterator<start, end, wrap<(start >= (end-1))> >
{
    static const null next;
};

class TS
{
private: TStates::States state;
public:
    TS() : state(TStates::A) {}
    
    void run();    
    
    template<TStates::States start, TStates::States end>
    void run_state(enum_iterator<start, end>);
    
    void run_state(null)
    {
        
    }
    
    template<TStates::States> void func();
};

#endif	/* TS_HPP */

