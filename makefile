db: main.o mcl.o
	g++ -fopenmp -O2 main.o mcl.o -o db
main.o: main.cpp mcl.h
	g++ -fopenmp -O2 main.cpp -c

mcl.o: mcl.cpp mcl.h
	g++ -fopenmp -O2 mcl.cpp -c

clean:
	rm db mcl.o main.o
