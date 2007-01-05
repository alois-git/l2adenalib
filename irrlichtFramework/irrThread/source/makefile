all: CThread.o CMutex.o
	g++ -shared -o irrThread.so irrThread.o
CThread.o:
	g++ -c -o CThread.o -I../include -I/cygdrive/c/Irrlicht-1.1/include CThread.cpp
CMutex.o:
	g++ -c -o CMutex.o -I../include -I/cygdrive/c/Irrlicht-1.1/include CMutex.cpp
test: CThread.o CMutex.o
	g++ -o test.exe -I../include -I/cygdrive/c/Irrlicht-1.1/include test.cpp CMutex.o CThread.o
clean:
	rm -rf *.o *.so *.exe *~