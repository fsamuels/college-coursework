all: testVector

testVector: testVector.o Vector.o
	g++ -o testVector testVector.o Vector.o

testVector.o: testVector.cpp
	g++ -c testVector.cpp

Vector.o: Vector.h Vector.cpp
	g++ -c Vector.cpp

clean:
	rm -f *.o
