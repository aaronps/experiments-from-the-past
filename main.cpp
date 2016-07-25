/* 
 * File:   main.cpp
 * Author: krom
 *
 * Created on December 5, 2012, 9:36 PM
 */

#include <stdio.h>
#include <cstdlib>
#include <pthread.h>

using namespace std;

class SimpleThread
{
public:
    SimpleThread()
    : started(false)
    {
    }
    
    virtual ~SimpleThread()
    {
        
    }
    
    virtual void run() = 0;
    
    bool start()
    {
        if ( ! started )
        {
            int rval = pthread_create( &thread, 0, thread_runner, (void*) this);
            started = rval == 0;
        }
        return started;
    }
    
    void join()
    {
        if ( started )
        {
            void * r;
            int rval = pthread_join(thread, &r);
            if ( rval == 0 )
            {
                started = false;
            }
        }
    }
    
protected:
    void end_thread(void *r)
    {
        started = false;
        pthread_exit(r);
    }
    
private:
    SimpleThread(const SimpleThread&);
    void operator=(const SimpleThread&);
    
    bool started;
    pthread_t thread;
    
    static void * thread_runner(void *data)
    {
        SimpleThread* obj = reinterpret_cast<SimpleThread*>(data);
        
        obj->run();
        
        obj->started = false;
        pthread_exit(0);
    }
};

class Lock
{
public:
    Lock(pthread_mutex_t * mutex) : mutex(mutex)
    {
        pthread_mutex_lock(mutex);
    }
    
    ~Lock()
    {
        pthread_mutex_unlock(mutex);
    }
private:
    Lock(const Lock& other);
    void operator=(const Lock&);
    pthread_mutex_t * mutex;
};

template<typename T>
class Lockable
{
public:
    Lockable() : mutex(PTHREAD_MUTEX_INITIALIZER)
    {
        
    }
    
    Lockable(const T& v) :mutex(PTHREAD_MUTEX_INITIALIZER), value(v)
    {
        
    }
    
    ~Lockable()
    {
        
    }
    
    pthread_mutex_t* lock()
    {
        return &mutex;
    }
    
    operator T() { return value; }
    
    void operator=(const T& v) { value = v; }
    void operator+=(const T& v) { value += v; }
    
private:
    pthread_mutex_t mutex;
    T value;
};

class PrintThread : public SimpleThread
{
public:
    PrintThread(const char * msg) : SimpleThread(), msg(msg)
    {
        
    }
    
    void run()
    {
        Sleep(1000);
        Lock guard(my_number.lock());
        my_number += 1;
        printf("I'm %d msg: %s\n", (int)my_number, msg);
        my_number += 1;
        printf("I'm %d msg: %s\n", (int)my_number, msg);
        my_number += 1;
        printf("I'm %d msg: %s\n", (int)my_number, msg);
        my_number += 1;
        printf("I'm %d msg: %s\n", (int)my_number, msg);
        my_number += 1;
        printf("I'm %d msg: %s\n", (int)my_number, msg);
    }
    
    static Lockable<int> my_number;
private:
    const char * msg;
    
};

Lockable<int> PrintThread::my_number(0);

/*
 * 
 */
int main(int argc, char** argv)
{
    PrintThread t1("hello 1");
    PrintThread t2("hello 2");
    PrintThread t3("hello 3");
    PrintThread t4("hello 4");
    
    t1.start();
    t2.start();
    t3.start();
    t4.start();
    
    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}

