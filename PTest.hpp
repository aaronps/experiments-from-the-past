/* 
 * File:   PTest.hpp
 * Author: krom
 *
 * Created on November 18, 2012, 4:18 PM
 */

#ifndef PTEST_HPP
#define	PTEST_HPP

class PTest
{
public:
    PTest();

    int hello;
    
    void (PTest::*fun)();
//    void *fun;
    
    void callIt()
    {
//        goto *fun;
        (((PTest*)this)->*fun)();
    }
    
    void nothing();
    
    
    void func_a();
    
    void func_b();
    
    
};

#endif	/* PTEST_HPP */

