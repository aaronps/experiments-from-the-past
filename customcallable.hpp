/*
 * File:   customcallable.hpp
 * Author: krom
 *
 * Created on November 29, 2010, 11:28 PM
 */

#ifndef CUSTOMCALLABLE_HPP
#define CUSTOMCALLABLE_HPP
class Callable
{
    public:
        virtual ~Callable()
        {
        }

        ;
        virtual void operator ()() = 0;
};


template<class C, void (C::*M)()>
class Ruin:
    public Callable
{
    public:
        C * obj;

        Ruin(C * o):
            obj(o)
        {
        }

        void operator ()()
        {
            (obj->*M)();
        }
};


template<class C, void (C::*m)()>
Callable * ss(C * o)
{
    return new Ruin<C, m>(o);
}

class CustomCallableSignal
{
    private:
        std::list<Callable *> listeners;

    public:
        CustomCallableSignal()
        {
        }

        ~CustomCallableSignal()
        {
            // destroy me
        }

        template<class T, void (T::*met)()>
        void connect(T * obj)
        {
            listeners.push_back(new Ruin<T, met>(obj));
        }

        void raise()
        {
            for (std::list<Callable *>::iterator i = listeners.begin(), e = listeners.end(); i != e; ++i)
            {
                (*i) -> operator ()();
            }
        }
};
#endif   /* CUSTOMCALLABLE_HPP */
