/*
 * File:   virtualcall.hpp
 * Author: krom
 *
 * Created on November 30, 2010, 7:59 AM
 */

#ifndef VIRTUALCALL_HPP
#define VIRTUALCALL_HPP

#include <list>

class EventListener
{
    public:
        EventListener()
        {
        }

        ;
        virtual ~EventListener()
        {
        }

        ;
        virtual void onEvent(const int) = 0;
};


class VirtualCallSignal
{
    private:
        std::list<EventListener *> listeners;

    public:
        VirtualCallSignal()
        {
        }

        ~VirtualCallSignal()
        {
            // destroy me
        }

        void addListener(EventListener * e)
        {
            listeners.push_back(e);
        }

        void raise() const
        {
#if 1
            std::list<EventListener *>::const_iterator i = listeners.begin(),
                                                       e = listeners.end();

            if (i != e)
            {
                do
                {
                    (*i) -> onEvent(1);
                }
                while (++i != e);
            }
#else
            for (std::list<EventListener *>::const_iterator i = listeners.begin(), e = listeners.end(); i != e; ++i)
            {
                (*i) -> onEvent();
            }
#endif

        }
};


// class TestVirtualCall
// {
// private:
// VirtualCallSignal signal;
// public:
// TestVirtualCall(){}
// ~TestVirtualCall(){}
//
// void add( EventListener *obj)
// {
// signal.addListener(obj);
// }
//
// void test();
//
// };
class TestSingleVirtualCall
{
    private:
        EventListener * signal;

    public:
        TestSingleVirtualCall()
        {
        }

        ~TestSingleVirtualCall()
        {
        }

        void connect(EventListener * obj)
        {
            signal = obj;
        }

        void test();
};
#endif   /* VIRTUALCALL_HPP */


//~ Formatted by Jindent --- http://www.jindent.com
