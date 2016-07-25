# Simple Thread

In this experiment in c++ I made on 2012, it includes some simple classes to use pthreads in a way somewhat similar to Java's Thread. I reused code similar to this in a couple of projects later.

There are class SimpleThread you need to override run(), a Lock class which autorelease the lock when goes out of scope (wasn't this called RAII?) and a Lockable template.

All very simple and easy to read.
