OPTION =  -O3 -Wall  

CC = gcc
C++ = g++

all:	RefGen

clean: 
	rm  RefGen 

RefGen:	main.cpp class.cpp class.hpp general.h general.cpp
	
	$(C++) -g -o RefGen general.cpp class.cpp main.cpp   $(OPTION)

