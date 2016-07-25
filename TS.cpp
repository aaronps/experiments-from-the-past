#include "TS.hpp"
#include <iostream>

using namespace std;

template<> inline void TS::func<TStates::A>() { cout << "Func A\n"; state = TStates::B; }
template<> inline void TS::func<TStates::B>() { cout << "Func B\n"; state = TStates::C; }
template<> inline void TS::func<TStates::C>() { cout << "Func C\n"; state = TStates::D; }
template<> inline void TS::func<TStates::D>() { cout << "Func D\n"; state = TStates::E; }
template<> inline void TS::func<TStates::E>() { cout << "Func E\n"; state = TStates::F; }
template<> inline void TS::func<TStates::F>() { cout << "Func F\n"; state = TStates::G; }
template<> inline void TS::func<TStates::G>() { cout << "Func G\n"; state = TStates::H; }
template<> inline void TS::func<TStates::H>() { cout << "Func H\n"; state = TStates::I; }
template<> inline void TS::func<TStates::I>() { cout << "Func I\n"; state = TStates::J; }
template<> inline void TS::func<TStates::J>() { cout << "Func J\n"; state = TStates::K; }
template<> inline void TS::func<TStates::K>() { cout << "Func K\n"; state = TStates::L; }
template<> inline void TS::func<TStates::L>() { cout << "Func L\n"; state = TStates::M; }
template<> inline void TS::func<TStates::M>() { cout << "Func M\n"; state = TStates::N; }
template<> inline void TS::func<TStates::N>() { cout << "Func N\n"; state = TStates::O; }
template<> inline void TS::func<TStates::O>() { cout << "Func O\n"; state = TStates::P; }
template<> inline void TS::func<TStates::P>() { cout << "Func P\n"; state = TStates::Q; }
template<> inline void TS::func<TStates::Q>() { cout << "Func Q\n"; state = TStates::A; }

template<TStates::States start, TStates::States end>
inline void TS::run_state(enum_iterator<start,end>)
{
    switch ( state )
    {
        case start:
            func<start>();
            break;
        default:
            run_state(enum_iterator<start,end>::next);
    }
    
//        if ( state == start )
//        {
//            func<start>();
//        }
//        else
//        {
//            run_state(enum_iterator<start,end>::next);
//        }
    
//        if ( state == start )
//        {
//            func<start>();
//        }
//        else
//        {
//            run_state(enum_iterator<start,end>::next);
//        }
    
//    (state == start) && (func<start>(), false) || (run_state(enum_iterator<start,end>::next), false);
    
    
}

void TS::run()
{
    run_state(enum_iterator<TStates::A,TStates::END>());
}
