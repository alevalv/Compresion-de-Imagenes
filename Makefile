default: all

CXXFLAGS = -O2

TransCoseno.o : TransCoseno.cpp TransCoseno.h
		g++ ${CXXFLAGS} -c TransCoseno.cpp

CompressorFile.o : CompressorFile.cpp CompressorFile.h
		    g++ ${CXXFLAGS} -c  CompressorFile.cpp

compresion: main.cpp TransCoseno.o CompressorFile.o
		g++ ${CXXFLAGS} -c main.cpp
		g++ ${CXXFLAGS} main.o TransCoseno.o CompressorFile.o -o compresion

all: compresion

