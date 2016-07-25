# Templated State Machine

This experiment from 2012, I tried to find a way to write less boilerplate when writting state machines and at the same time to make it fast. At this time I was making experiments with templates.

I had fun doing this, I would compile it to assembly then inspect the generated code to see the results, these asm files are in build/{Debug,Release}_ASM/MinGW-Windows/main.o -> it is not a binary file, it is the generated code.

One thing I learned and used it later was that you could write a templated definition in the header file, and write multiple implementations of it with different templated values... somewhat saving some typing... maybe not the best idea but interesting nonetheless, it proved usefull later on some other projects.

More or less the implementations were:

* `PTest` -> Pointer based state machine, the state function is a pointer to a method: `void (PTest::*fun)();` just call it... i forgot to add state changing logic, lol.

* `SWMachine` -> `switch` machine, the run method is a big `switch`: easy and maybe fast, but all the code is in a big function.

* `SWMachineB` -> Like `SWMachine` but the switch calls a `state_XXX` method, code may be more readable but extra typing.

* `TS` -> Templated State, this one was tricky to get working, but it generated the `switch` which would call the correct member function for the state, using a recursive template (_I think that was the name_). This had less typing than other methods *when adding new states* but the generated code was not so nice, usually was a `cmp x,y; je ...`.

* `TSB` -> A revision of `TS` merging with `SWMachineB` this one had more or less low typing and was generating nice code.

For TSB he header file was nice:
```c++
class TSB
{
private:
    typedef enum { A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, END } States;
    States state;
    
public:
    TSB() : state(A) {}
    
    void run();    
    
    template<States> void func();
};
```

So there was only one definition of `func` and in the implementation file, we created all of them, the compiler would complain if you forgot to implement one state and it would complain if you tried to use an state not in the `enum`... nice!!!
