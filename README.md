Tinyweb
=======

Functions for simple network programming


======

Building the static library.
1. `gcc -c tinyweb.c`
2. `ar rs libtinyweb.a tinyweb.o`


Building the shared library.
1. `gcc -fpic -c tinyweb.c`
2. gcc -shared -o libtinyweb.so tinyweb.o`
3. `cp libtinyweb.so /usr/lib`
