#include "PTest.hpp"
#include <iostream>

using namespace std;

PTest::PTest()
{
//    fun = (void*)(&PTest::func_b);
    fun = &PTest::func_b;
}

void PTest::func_a()
{
    cout << "called a" << endl;
}

void PTest::func_b()
{
    cout << "called b" << endl;
}

void PTest::nothing()
{
    cout << "this is nothing" << endl;
}
