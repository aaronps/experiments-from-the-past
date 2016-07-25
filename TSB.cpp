#include "TSB.hpp"
#include <iostream>

using namespace std;

template<> inline void TSB::func<TSB::A>() { cout << "Bunc A\n"; state = TSB::B; }
template<> inline void TSB::func<TSB::B>() { cout << "Bunc B\n"; state = TSB::C; }
template<> inline void TSB::func<TSB::C>() { cout << "Bunc C\n"; state = TSB::D; }
template<> inline void TSB::func<TSB::D>() { cout << "Bunc D\n"; state = TSB::E; }
template<> inline void TSB::func<TSB::E>() { cout << "Bunc E\n"; state = TSB::F; }
template<> inline void TSB::func<TSB::F>() { cout << "Bunc F\n"; state = TSB::G; }
template<> inline void TSB::func<TSB::G>() { cout << "Bunc G\n"; state = TSB::H; }
template<> inline void TSB::func<TSB::H>() { cout << "Bunc H\n"; state = TSB::I; }
template<> inline void TSB::func<TSB::I>() { cout << "Bunc I\n"; state = TSB::J; }
template<> inline void TSB::func<TSB::J>() { cout << "Bunc J\n"; state = TSB::K; }
template<> inline void TSB::func<TSB::K>() { cout << "Bunc K\n"; state = TSB::L; }
template<> inline void TSB::func<TSB::L>() { cout << "Bunc L\n"; state = TSB::M; }
template<> inline void TSB::func<TSB::M>() { cout << "Bunc M\n"; state = TSB::N; }
template<> inline void TSB::func<TSB::N>() { cout << "Bunc N\n"; state = TSB::O; }
template<> inline void TSB::func<TSB::O>() { cout << "Bunc O\n"; state = TSB::P; }
template<> inline void TSB::func<TSB::P>() { cout << "Bunc P\n"; state = TSB::Q; }
template<> inline void TSB::func<TSB::Q>() { cout << "Bunc Q\n"; state = TSB::A; }

void TSB::run()
{
    switch (state)
    {
#define CASE(X) case X: func<X>(); break;
        CASE(TSB::A)
        CASE(TSB::B)
        CASE(TSB::C)
        CASE(TSB::D)
        CASE(TSB::E)
        CASE(TSB::F)
        CASE(TSB::G)
        CASE(TSB::H)
        CASE(TSB::I)
        CASE(TSB::J)
        CASE(TSB::K)
        CASE(TSB::L)
        CASE(TSB::M)
        CASE(TSB::N)
        CASE(TSB::O)
        CASE(TSB::P)
        CASE(TSB::Q)
#undef CASE
    }
}
