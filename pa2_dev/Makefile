all: main clean
main: main.cpp block.o
	g++ -g -Wall main.cpp block.o -o main

block.o: block.cpp
	g++ -g -Wall block.cpp -c
clean:
	rm block.o
clear: 
	rm main