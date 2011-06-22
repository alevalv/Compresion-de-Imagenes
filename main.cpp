
#include <iostream>
#include <vector>
#include "TransCoseno.h"
#include "CompressorFile.h"
#include "LeerImagen.h"
#include <cassert>
#include <stdio.h>
using namespace std;

int main(int argvs, char* args[]){
	assert(argvs==2);
	LeerImagen a(args[1]);
	vector<vector<int> > matrizImagen = a.getMatriz();
	vector<vector<double> > tuplass=TransCoseno::comprimirImagen(matrizImagen);
	CompressorFile cf((int)matrizImagen.size(),(int)matrizImagen[0].size(), 8.0, tuplass);
	cf.CreateFile("file.txt");

	cf.ReadCompressedFile("file.txt");
}
