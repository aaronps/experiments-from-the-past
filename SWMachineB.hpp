/* 
 * File:   SWMachineB.hpp
 * Author: krom
 *
 * Created on November 19, 2012, 8:42 PM
 */

#ifndef SWMACHINEB_HPP
#define	SWMACHINEB_HPP

struct TStatesSWB
{
    typedef enum { A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, END } values;
};

class SWMachineB
{
private:
    TStatesSWB::values state;
    
public:
    SWMachineB() :state(TStatesSWB::A){}
    
    void run();
    
    void state_A();
    void state_B();
    void state_C();
    void state_D();
    void state_E();
    void state_F();
    void state_G();
    void state_H();
    void state_I();
    void state_J();
    void state_K();
    void state_L();
    void state_M();
    void state_N();
    void state_O();
    void state_P();
    void state_Q();
};

#endif	/* SWMACHINEB_HPP */

