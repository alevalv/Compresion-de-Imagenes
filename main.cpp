#include <iostream>
#include <vector>
#include "TransCoseno.h"
#include "CompressorFile.h"
#include "LeerImagen.h"
#include "BlockMatching.h"
#include "ComprimirVideo.h"
#include <cassert>
#include <stdio.h>
#include <cstdlib>
using namespace std;

int main(int argvs, char* args[]){
	assert(argvs>2);	
	string opt(args[1]);
	if(opt=="-cm"){
		assert(argvs>=5);
		LeerImagen a(args[2]);
		vector<vector<int> > matrizImagen = a.getMatriz();
		vector<vector<double> > tuplass=TransCoseno::comprimirImagen(matrizImagen, atoi(args[3]));
		CompressorFile cf((int)matrizImagen.size(),(int)matrizImagen[0].size(), 8.0, tuplass);
		cf.CreateFile(args[4]);	
	}
	else if(opt=="-uncm"){		
		assert(argvs>=4);
		CompressorFile cf;
		vector<vector<double> > tuplasImagen=cf.ReadCompressedFile(string(args[2]));		
		vector<vector<double> > Imagen=TransCoseno::descomprimirImagen(cf.getWidth(),cf.getHeight(),tuplasImagen);
		cf.CreateImagenDescomprimida(Imagen, args[3]);
	}
	else if(opt=="-cmvid"){
		assert(argvs>=4);
		string entrada(args[2]);
		ComprimirVideo compresor(entrada, atoi(args[3]));
		compresor.comprimirImagenes();
	}
	else if(opt=="-uncmvid"){
		assert(argvs>=4);
		string entrada(args[2]);
		ComprimirVideo compresor(entrada, atoi(args[3]));
		compresor.descomprimirImagenes();
	}
	else{
		cerr<<"Opción no reconocida"<<endl;
	}
}
