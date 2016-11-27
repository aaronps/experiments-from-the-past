/* 
 * File:   SomeClass.hpp
 * Author: krom
 *
 * Created on February 23, 2013, 8:33 AM
 */

#ifndef SOMECLASS_HPP
#define	SOMECLASS_HPP

#include "Action.hpp"

class SomeClass
{
public:
    SomeClass(){}

    typedef class Ac1 : public Action{public: void execute();} TypedAc1;
    typedef class Ac2 : public Action{public: void execute();} TypedAc2;

    TypedAc1 action_1;
    TypedAc2 action_2;

};

#endif	/* SOMECLASS_HPP */

