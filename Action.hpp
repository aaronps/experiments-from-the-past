/* 
 * File:   Action.hpp
 * Author: krom
 *
 * Created on February 23, 2013, 8:33 AM
 */

#ifndef ACTION_HPP
#define	ACTION_HPP

class Action
{
private:
    Action(const Action&);
    void operator=(const Action&);

public:
    Action(){}
    virtual ~Action() {}
    virtual void execute() = 0;
};

#endif	/* ACTION_HPP */

