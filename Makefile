############ Makefile grafo ###############
all: build

exec:
	./a.out

build: bipartido.o
	g++ -std=c++14 main.cpp bipartido.o -g

bipartido.o:
	g++ -std=c++14 -c bipartido.cpp -g

clear:
	rm -rf *.o *.out