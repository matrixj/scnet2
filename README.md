scnet2: A network programming library
Authors: matrixj (chenjieqiang@gmail.com)

The coid under this directory implements a system for maintaining a network programming library.

See doc/xxx  for more explanation.
See doc/impl.html for a brief overview of the implementation.

The public interface is in src/base/*.h.Callers should not include or rely on the details of any other header files in this package.Those internal APIs may be changed without warning.

Guide to header files:

src/base/BaseLoop.h
    Main eventloop interface to the lib: Start here;
src/base/logbuffer.h
    Log interface to the lib:if you want to log in your program;If you want to use it, look at  src/base/test/logger.cc for example;
......
### Working on branch lua-coroutine, trying actor model with  lua :) ###
