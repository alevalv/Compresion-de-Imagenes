#include <iostream>
#include <vector>
#include "TransCoseno.h"
#include "CompressorFile.h"
#include "LeerImagen.h"
#include <cassert>
#include <stdio.h>
using namespace std;

int main(int argvs, char* args[]){
	assert(argvs>2);	
	string opt(args[1]);
	if(opt=="-cm"){
		assert(argvs>=4);
		LeerImagen a(args[2]);
		vector<vector<int> > matrizImagen = a.getMatriz();
		vector<vector<double> > tuplass=TransCoseno::comprimirImagen(matrizImagen);
		CompressorFile cf((int)matrizImagen.size(),(int)matrizImagen[0].size(), 8.0, tuplass);
		cf.CreateFile(args[3]);	
	}
	else if(opt=="-uncm"){		
		assert(argvs>=3);
		CompressorFile cf;
		vector<vector<double> > tuplasImagen=cf.ReadCompressedFile(string(args[2]));
		vector<vector<double> > Imagen=TransCoseno::descomprimirImagen(800,800,tuplasImagen);
		cf.CreateImagenDescomprimida(Imagen, "wonitod.pgm");
	}
}
