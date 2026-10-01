# ThreadSafeQueue
A small C++ library that lets multiple threads safely share a queue - one thread can add items while others take them out, without stepping on each other's toes.

## Why I built this
After building a multi-threaded chat-server, I wanted to practice writing a small, reusable, well-tested piece of code, the kind of thing a bigger project might actually depend on, instead of just locking things inline wherever needed.

## What it does
- Add items to the queue ('push')
- Take items out, waiting if it's empty ('pop')
- Take items out without waiting ('try_pop')
- Tell the queue "no more items are coming" so any waiting threads can stop cleanly ('shutdown')

## Building and testing it
You need 'cmake' and a C++ compiler. The test framework (Catch2) downloads itself automatically the first time build, so there's nothing extra to install

```bash
mkdir build && cd build
cmake ..
make
./tests
```
