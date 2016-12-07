cp : main.o processing.o closest_pair.o
	g++ -o cp main.o processing.o closest_pair.o

main.o : main.cpp headers.h
	g++ -c main.cpp
processing.o : processing.cpp processing.h headers.h
	g++ -c processing.cpp
closest_pair.o : closest_pair.cpp closest_pair.h headers.h
	g++ -c closest_pair.cpp
clean :
	rm cp main.o processing.o closest_pair.o
