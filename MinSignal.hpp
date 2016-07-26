#ifndef MINSIGNAL_HPP
#define MINSIGNAL_HPP


class DUMMYCLASS;

struct MinSignalData
{
    DUMMYCLASS * object;
    void (DUMMYCLASS::*method)();
};

class MinSignal
{
private:
    MinSignalData listener;
public:
    MinSignal() {}
    ~MinSignal()
    {}

    template<class T>
    void connect( T *obj, void(T::*met)() )
    {
        this->listener.object = (DUMMYCLASS*)obj;
        this->listener.method = (void (DUMMYCLASS::*)())met;
    }

    void operator()()
    {
        this->raise();
    }

    void raise()
    {
        (this->listener.object->*(this->listener).method)();
    }

};


#endif // MINSIGNAL_HPP
