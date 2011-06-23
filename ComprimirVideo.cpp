#include "ComprimirVideo.h"
#include "CompressorFile.h"
#include "TransCoseno.h"
#include <math.h>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>

using namespace std;

vector<vector<double> > operator-(const vector<vector<double> >& a, const vector<vector<double> >& b){
	int w=a.size(), h=a[0].size();
	vector<vector<double> > resultado(w, vector<double>(h, 0));
	for(int i=0;i<w;i++)
	    for(int j=0;j<h;j++)
		resultado[i][j]=a[i][j]-b[i][j];
	return resultado;
}

ComprimirVideo::ComprimirVideo(string prefijo, int numero_imagenes){
	this->prefijo=prefijo;
	IMAGE_NUMBER=numero_imagenes;
	
}
/*
void ComprimirVideo::comprimirImagenes(){
   int i=0;
   while(true){
      ifstream FileIn(prefijo.c_str(), ios::in);
      if(!FileIn.is_open()) return;
   }
}
*/

void ComprimirVideo::comprimirFotograma(vector<vector<double> >& anterior, vector<vector<double> >& actual, string path){
	vector<vector<double> > matrizImagen = actual-anterior;
	vector<vector<double> > tuplass=TransCoseno::comprimirImagen(matrizImagen);
	CompressorFile cf((int)matrizImagen.size(),(int)matrizImagen[0].size(), 8.0, tuplass);
	cf.CreateFile(path);	
}
