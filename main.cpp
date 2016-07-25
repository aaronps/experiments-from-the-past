/* 
 * File:   main.cpp
 * Author: krom
 *
 * Created on November 18, 2012, 4:06 PM
 */

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

template<typename T, T first, T last>
struct enum_iterator
{
    static const T first_value = first;
    static const T last_value = last;
    
    template<T val>
    struct next
    {
        static const T value = (T)(val+1);
    };
};

class StateMan
{
private:
    struct States
    {
        typedef enum { A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, END } Enum;
    };
    
    typedef enum_iterator<States::Enum, States::A, States::END> StatesIter;
    
    States::Enum state;
    
public:
    StateMan() : state(States::A)
    {
        
    }
//    StateMan() {}

    void setRandomState()
    {
        state = States::Enum(rand() % StatesIter::last_value);
    }
    
    void run_state()
    {
        gswitch<StatesIter::first_value>(StatesIter::first_value);
    }
    
    template<States::Enum> void gswitch(const States::Enum);
    template<States::Enum> void state_func();
};

// <editor-fold desc="state funcs" defaultstate="collapsed">

template<> inline void StateMan::state_func<StateMan::States::A>() { cout << "Func A\n"; state = StateMan::States::B; }
template<> inline void StateMan::state_func<StateMan::States::B>() { cout << "Func B\n"; state = StateMan::States::C; }
template<> inline void StateMan::state_func<StateMan::States::C>() { cout << "Func C\n"; state = StateMan::States::D; }
template<> inline void StateMan::state_func<StateMan::States::D>() { cout << "Func D\n"; state = StateMan::States::E; }
template<> inline void StateMan::state_func<StateMan::States::E>() { cout << "Func E\n"; state = StateMan::States::F; }
template<> inline void StateMan::state_func<StateMan::States::F>() { cout << "Func F\n"; state = StateMan::States::G; }
template<> inline void StateMan::state_func<StateMan::States::G>() { cout << "Func G\n"; state = StateMan::States::H; }
template<> inline void StateMan::state_func<StateMan::States::H>() { cout << "Func H\n"; state = StateMan::States::I; }
template<> inline void StateMan::state_func<StateMan::States::I>() { cout << "Func I\n"; state = StateMan::States::J; }
template<> inline void StateMan::state_func<StateMan::States::J>() { cout << "Func J\n"; state = StateMan::States::K; }
template<> inline void StateMan::state_func<StateMan::States::K>() { cout << "Func K\n"; state = StateMan::States::L; }
template<> inline void StateMan::state_func<StateMan::States::L>() { cout << "Func L\n"; state = StateMan::States::M; }
template<> inline void StateMan::state_func<StateMan::States::M>() { cout << "Func M\n"; state = StateMan::States::N; }
template<> inline void StateMan::state_func<StateMan::States::N>() { cout << "Func N\n"; state = StateMan::States::O; }
template<> inline void StateMan::state_func<StateMan::States::O>() { cout << "Func O\n"; state = StateMan::States::P; }
template<> inline void StateMan::state_func<StateMan::States::P>() { cout << "Func P\n"; state = StateMan::States::Q; }
template<> inline void StateMan::state_func<StateMan::States::Q>() { cout << "Func Q\n"; state = StateMan::States::A; }
// </editor-fold>

template<>
void StateMan::gswitch<StateMan::StatesIter::last_value>(const StateMan::States::Enum)
{
    
}

template<StateMan::States::Enum E>
void StateMan::gswitch(const StateMan::States::Enum)
{
    if ( state == E )
    {
        state_func<E>();
        return;
    }
    gswitch<StateMan::StatesIter::next<E>::value>(StateMan::StatesIter::next<E>::value);
}

int main(int argc, char** argv)
{
    srand(time(0));
    StateMan sm;
    
    sm.setRandomState();
    sm.run_state();
    sm.setRandomState();
    sm.run_state();
    sm.setRandomState();
    sm.run_state();
    
    return 0;
}

