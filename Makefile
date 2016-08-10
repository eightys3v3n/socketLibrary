gcc=gcc --std=c++17 -Wall -Wextra
ar=ar crf

all: socket_test

# make-able targets
libsocket.a: socket.o
	$(ar) libsocket.a socket.o

libsocket.so: socket_pic.o
	$(gcc) -shared socket_pic.o -o libsocket.so

socket_test: socket_test.o libsocket.a libsocket_tests.a
	$(gcc) socket_test.o -o socket_test libsocket_tests.a libsocket.a -lstdc++

libsocket_tests.a: libsocket.a socket_tests.o socket.o
	$(ar) libsocket_tests.a socket_tests.o




# static libraries
socket.o: socket.cpp
	$(gcc) -c socket.cpp -o socket.o




# shared libraries
socket_pic.o: socket.cpp
	$(gcc) -fpic -c socket.cpp -o socket_pic.o




# stand-alone testing binary
socket_test.o: socket_test.cpp
	$(gcc) -c socket_test.cpp -o socket_test.o




# static testing library
socket_tests.o: socket_tests.cpp
	$(gcc) -c socket_tests.cpp -o socket_tests.o




clean:
	rm -rf *.o