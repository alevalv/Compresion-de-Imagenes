default: all

CXXFLAGS = -O2

LeerImagen.o : LeerImagen.cpp LeerImagen.h
	       g++ ${CXXFLAGS} -c LeerImagen.cpp

TransCoseno.o : TransCoseno.cpp TransCoseno.h
		g++ ${CXXFLAGS} -c TransCoseno.cpp

CompressorFile.o : CompressorFile.cpp CompressorFile.h
		    g++ ${CXXFLAGS} -c  CompressorFile.cpp

BlockMatching.o: BlockMatching.cpp BlockMatching.h
		    g++ ${CXXFLAGS} -c  BlockMatching.cpp

compresion: main.cpp LeerImagen.o TransCoseno.o CompressorFile.o BlockMatching.o
		g++ ${CXXFLAGS} -c main.cpp
		g++ ${CXXFLAGS} main.o LeerImagen.o TransCoseno.o CompressorFile.o BlockMatching.o -o compresion

all: compresion

