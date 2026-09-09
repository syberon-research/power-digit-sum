all: main-program

main-program: power-digit-sum.cpp
	g++ -Wall -O3 -g -std=c++17 power-digit-sum.cpp -o pds