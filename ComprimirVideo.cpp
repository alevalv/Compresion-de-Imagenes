#include "ComprimirVideo.h"
#include "CompressorFile.h"
#include "TransCoseno.h"
#include "LeerImagen.h"
#include <math.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cstdio>
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

vector<vector<double> > operator-(const vector<vector<int> >& a, const vector<vector<int> >& b){
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

void ComprimirVideo::comprimirImagenes(){
	string firstimage=prefijo+"0.pgm";
	LeerImagen li(firstimage);
	vector<vector<int> > anterior=li.getMatriz();
	vector<vector<double> > tuplass=TransCoseno::comprimirImagen(anterior);
	CompressorFile cf((int)anterior.size(),(int)anterior[0].size(), 8.0, tuplass);
	cf.CreateFile("comprimida0.cvca");
	char bff [4];
	for(int i=1;i<IMAGE_NUMBER;i++){
		sprintf (bff, "%d", i);	
		string numero(bff);	
		string actpath=prefijo+numero+".pgm";
		LeerImagen li(actpath);
		vector<vector<int> > actual=li.getMatriz();
		vector<vector<double> > residual=actual-anterior;
		vector<vector<double> > tuplass=TransCoseno::comprimirImagen(residual);
		CompressorFile cf((int)anterior.size(),(int)anterior[0].size(), 8.0, tuplass);
		cf.CreateFile("comprimida"+numero+".cvca");
		anterior=actual;
		actual.clear();
	}
}

void ComprimirVideo::comprimirFotograma(vector<vector<double> >& anterior, vector<vector<double> >& actual, string path){
	vector<vector<double> > matrizImagen = actual-anterior;
	vector<vector<double> > tuplass=TransCoseno::comprimirImagen(matrizImagen);
	CompressorFile cf((int)matrizImagen.size(),(int)matrizImagen[0].size(), 8.0, tuplass);
	cf.CreateFile(path);	
}
