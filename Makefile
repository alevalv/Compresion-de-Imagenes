default: all

CXXFLAGS = -Wall -O2

TransCoseno.o : TransCoseno.cpp TransCoseno.h
		g++ ${CXXFLAGS} -c TransCoseno.cpp

compresion: main.cpp TransCoseno.o
		g++ ${CXXFLAGS} -c main.cpp
		g++ ${CXXFLAGS} main.o TransCoseno.o -o compresion

all: compresion

