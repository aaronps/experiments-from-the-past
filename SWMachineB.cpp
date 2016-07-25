#include "SWMachineB.hpp"
#include <iostream>

using namespace std;

void SWMachineB::run()
{
    switch (state)
    {
        case TStatesSWB::A: state_A(); break;
        case TStatesSWB::B: state_B(); break;
        case TStatesSWB::C: state_C(); break;
        case TStatesSWB::D: state_D(); break;
        case TStatesSWB::E: state_E(); break;
        case TStatesSWB::F: state_F(); break;
        case TStatesSWB::G: state_G(); break;
        case TStatesSWB::H: state_H(); break;
        case TStatesSWB::I: state_I(); break;
        case TStatesSWB::J: state_J(); break;
        case TStatesSWB::K: state_K(); break;
        case TStatesSWB::L: state_L(); break;
        case TStatesSWB::M: state_M(); break;
        case TStatesSWB::N: state_N(); break;
        case TStatesSWB::O: state_O(); break;
        case TStatesSWB::P: state_P(); break;
        case TStatesSWB::Q: state_Q(); break;
    }
}

inline void SWMachineB::state_A() { cout << "FSWM-- A\n"; state = TStatesSWB::B; }
inline void SWMachineB::state_B() { cout << "FSWM-- B\n"; state = TStatesSWB::C; }
inline void SWMachineB::state_C() { cout << "FSWM-- C\n"; state = TStatesSWB::D; }
inline void SWMachineB::state_D() { cout << "FSWM-- D\n"; state = TStatesSWB::E; }
inline void SWMachineB::state_E() { cout << "FSWM-- E\n"; state = TStatesSWB::F; }
inline void SWMachineB::state_F() { cout << "FSWM-- F\n"; state = TStatesSWB::G; }
inline void SWMachineB::state_G() { cout << "FSWM-- G\n"; state = TStatesSWB::H; }
inline void SWMachineB::state_H() { cout << "FSWM-- H\n"; state = TStatesSWB::I; }
inline void SWMachineB::state_I() { cout << "FSWM-- I\n"; state = TStatesSWB::J; }
inline void SWMachineB::state_J() { cout << "FSWM-- J\n"; state = TStatesSWB::K; }
inline void SWMachineB::state_K() { cout << "FSWM-- K\n"; state = TStatesSWB::L; }
inline void SWMachineB::state_L() { cout << "FSWM-- L\n"; state = TStatesSWB::M; }
inline void SWMachineB::state_M() { cout << "FSWM-- M\n"; state = TStatesSWB::N; }
inline void SWMachineB::state_N() { cout << "FSWM-- N\n"; state = TStatesSWB::O; }
inline void SWMachineB::state_O() { cout << "FSWM-- O\n"; state = TStatesSWB::P; }
inline void SWMachineB::state_P() { cout << "FSWM-- P\n"; state = TStatesSWB::Q; }
inline void SWMachineB::state_Q() { cout << "FSWM-- Q\n"; state = TStatesSWB::A; }

