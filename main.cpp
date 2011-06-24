#include <iostream>
#include <vector>
#include "TransCoseno.h"
#include "CompressorFile.h"
#include "LeerImagen.h"
#include "BlockMatching.h"
#include "ComprimirVideo.h"
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
		assert(argvs>=4);
		CompressorFile cf;
		vector<vector<double> > tuplasImagen=cf.ReadCompressedFile(string(args[2]));		
		vector<vector<double> > Imagen=TransCoseno::descomprimirImagen(cf.getWidth(),cf.getHeight(),tuplasImagen);
		cf.CreateImagenDescomprimida(Imagen, args[3]);
	}
	else if(opt=="-test"){
		string entrada(args[2]);
		string entrada2(args[3]);
		LeerImagen a(entrada);
		LeerImagen b(entrada2);
		vector<vector<int> > ma=a.getMatriz();
		vector<vector<int> > mb=b.getMatriz();
		BlockMatching bm(ma, mb);
		vector<int> salida=bm.buscarBloque(80,80);
		for(int i=0;i<salida.size();i++){
			cerr<<salida[i]<<" ";
		}
	}
	else if(opt=="-cmvid"){
		string entrada(args[2]);
		//string entrada2(args[3]);
		ComprimirVideo compresor(entrada, 9);
		compresor.comprimirImagenes();
	}
	else if(opt=="-uncmvid"){
		string entrada(args[2]);
		ComprimirVideo compresor(entrada, 9);
		compresor.descomprimirImagenes();
	}
}
