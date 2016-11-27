/* 
 * File:   sfsigslot.hpp
 * Author: krom
 *
 * Created on November 29, 2010, 10:44 PM
 */

#ifndef SFSIGSLOT_HPP
#define	SFSIGSLOT_HPP

#include <list>
#include <algorithm>

class DUMMYCLASS;

class SFSignal;
typedef SFSignal SFConnection;

struct SFSignalData
{
    DUMMYCLASS * object;
    void (DUMMYCLASS::*method)(const int);
    void operator()(const int n)
    {
        (object->*method)(n);
    }

    template<class T>
    void newconnect( T *obj, void(T::*met)(const int) )
    {
	object = (DUMMYCLASS*)obj;
	method = (void (DUMMYCLASS::*)(int))met;
    }
};

class TestSFSignalData
{
private:
    SFSignalData signal;
public:
    TestSFSignalData(){}
    ~TestSFSignalData(){}
    
    template<class T>
    void connect( T *obj, void(T::*met)(const int) )
    {
        signal.newconnect<T>(obj,met);
    }
    
    void test();
    
};

//class SFSignal
//{
//private:
//    std::list<SFSignalData> listeners;
//    std::list<SFSignalData> connections;
//public:
//    SFSignal() {}
//    ~SFSignal()
//    {
//        // destroy me
//    }
//    
//    template<class T>
//    void connect(T *obj, void(T::*met)() )
//    {
//        SFSignalData sdata = {(DUMMYCLASS*)obj, (void (DUMMYCLASS::*)())met};
//        listeners.push_back(sdata);
//    }
//
//    void disconnect(SFConnection & connection)
//    {
//        
//    }
//    
//    void raise() const
//    {
//#if 1
//	std::list<SFSignalData>::const_iterator i = listeners.begin(), e = listeners.end();
//	if ( i != e ) do
//	{
//		((*i).object->*(*i).method)();	
//	} while ( ++i != e );
//#else
//        for ( std::list<SFSignalData>::const_iterator i = listeners.begin(), e = listeners.end();
//                i != e; ++i )
//        {
//            ((*i).object->*(*i).method)();
//        }
//#endif
//    }
//    
//};

//class TestSFSignal
//{
//private:
//    SFSignal signal;
//public:
//    TestSFSignal(){}
//    ~TestSFSignal(){}
//    
//    template<class T>
//    void add( T *obj, void(T::*met)() )
//    {
//        signal.connect<T>(obj,met);
//    }
//    
//    void test();
//    
//};



#endif	/* SFSIGSLOT_HPP */

