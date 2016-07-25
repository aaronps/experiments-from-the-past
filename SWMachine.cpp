#include "SWMachine.hpp"
#include <iostream>

using namespace std;

void SWMachine::run()
{
    switch (state)
    {
        case TStatesSW::A: cout << "FSWM A\n"; state = TStatesSW::B; break;
        case TStatesSW::B: cout << "FSWM B\n"; state = TStatesSW::C; break;
        case TStatesSW::C: cout << "FSWM C\n"; state = TStatesSW::D; break;
        case TStatesSW::D: cout << "FSWM D\n"; state = TStatesSW::E; break;
        case TStatesSW::E: cout << "FSWM E\n"; state = TStatesSW::F; break;
        case TStatesSW::F: cout << "FSWM F\n"; state = TStatesSW::G; break;
        case TStatesSW::G: cout << "FSWM G\n"; state = TStatesSW::H; break;
        case TStatesSW::H: cout << "FSWM H\n"; state = TStatesSW::I; break;
        case TStatesSW::I: cout << "FSWM I\n"; state = TStatesSW::J; break;
        case TStatesSW::J: cout << "FSWM J\n"; state = TStatesSW::K; break;
        case TStatesSW::K: cout << "FSWM K\n"; state = TStatesSW::L; break;
        case TStatesSW::L: cout << "FSWM L\n"; state = TStatesSW::M; break;
        case TStatesSW::M: cout << "FSWM M\n"; state = TStatesSW::N; break;
        case TStatesSW::N: cout << "FSWM N\n"; state = TStatesSW::O; break;
        case TStatesSW::O: cout << "FSWM O\n"; state = TStatesSW::P; break;
        case TStatesSW::P: cout << "FSWM P\n"; state = TStatesSW::Q; break;
        case TStatesSW::Q: cout << "FSWM Q\n"; state = TStatesSW::A; break;
    }
}
