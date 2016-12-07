edit : main.o pre_processing.o closest_pair.o
	g++ -o edit main.o pre_processing.o closest_pair.o

main.o : main.cpp headers.h
	g++ -c main.cpp
pre_processing.o : pre_processing.cpp pre_processing.h headers.h
	g++ -c pre_processing.cpp
closest_pair.o : closest_pair.cpp closest_pair.h headers.h
	g++ -c closest_pair.cpp
clean :
	rm edit main.o pre_processing.o closest_pair.o
