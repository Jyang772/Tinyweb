Tinyweb
=======

Functions for simple network programming


======

Building the static library.

 `gcc -c tinyweb.c`

 `ar rs libtinyweb.a tinyweb.o`


Building the shared library.

 `gcc -fpic -c tinyweb.c`

 `gcc -shared -o libtinyweb.so tinyweb.o`

 `cp libtinyweb.so /usr/lib`


References:

http://crasseux.com/books/ctutorial/Building-a-library.html

http://randu.org/tutorials/c/libraries.php
