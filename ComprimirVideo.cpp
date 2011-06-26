#include "ComprimirVideo.h"
#include "CompressorFile.h"
#include "TransCoseno.h"
#include "LeerImagen.h"
#include "BlockMatching.h"
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

vector<vector<double> > operator+(const vector<vector<double> >& a, const vector<vector<double> >& b){
	int w=a.size(), h=a[0].size();
	vector<vector<double> > resultado(w, vector<double>(h, 0));
	for(int i=0;i<w;i++)
	    for(int j=0;j<h;j++)
		resultado[i][j]=a[i][j]+b[i][j];
	return resultado;
}

vector<vector<double> > operator+(const vector<vector<double> >& a, const vector<vector<int> >& b){
	int w=a.size(), h=a[0].size();
	vector<vector<double> > resultado(w, vector<double>(h, 0));
	for(int i=0;i<w;i++)
	    for(int j=0;j<h;j++)
		resultado[i][j]=a[i][j]+b[i][j];
	return resultado;
}

ComprimirVideo::ComprimirVideo(string prefijo, int numero_imagenes){
	this->prefijo=prefijo;
	IMAGE_NUMBER=numero_imagenes;	
}

void ComprimirVideo::comprimirImagenes(){
	string firstimage=prefijo+"1.pgm";
	LeerImagen li(firstimage);
	vector<vector<int> > anterior=li.getMatriz();
	vector<vector<double> > tuplass=TransCoseno::comprimirImagen(anterior, 12);
	CompressorFile cf((int)anterior.size(),(int)anterior[0].size(), 8.0, tuplass);
	cf.CreateFile("comprimida1.cvca");
	char bff [4];
	for(int i=2;i<=IMAGE_NUMBER;i++){
		sprintf (bff, "%d", (i));	
		string numero(bff);	
		string actpath=prefijo+numero+".pgm";
		cerr<<actpath<<endl;
		LeerImagen li(actpath);
		vector<vector<int> > actual=li.getMatriz();
		string newpath="comprimida"+numero+".cvca";
		comprimirFotograma(anterior, actual, newpath);
		anterior=actual;
		actual.clear();
	}
}

void ComprimirVideo::descomprimirImagenes(){
	string firstimage=prefijo+"1.cvca";
	CompressorFile cf;
	vector<vector<double> > tuplasImagen=cf.ReadCompressedFile(firstimage);
	vector<vector<double> > anterior=TransCoseno::descomprimirImagen(cf.getWidth(),cf.getHeight(),tuplasImagen);	
	cf.CreateImagenDescomprimida(anterior, "descomprimida1.pgm");
	char bff [4];
	for(int i=2;i<=IMAGE_NUMBER;i++){
		sprintf (bff, "%d", (i));	
		string numero(bff);	
		string actpath=prefijo+numero+".cvca";
		tuplasImagen=cf.ReadCompressedFile(actpath);	
		vector<vector<double> > actual=descomprimirFotograma(cf.getWidth(), cf.getHeight(),tuplasImagen, anterior);		
		string newpath="descomprimida"+numero+".pgm";
		cf.CreateImagenDescomprimida(actual, newpath);
		anterior=actual;
		actual.clear();
	}
}


vector<vector<double> > agregarVectoresDirectores(vector<vector<double> >& tuplas, vector<vector<int> >& vectoresDir){
	vector<vector<double> > newTuplas;
	newTuplas.reserve(tuplas.size());
	for(int i=0;i<tuplas.size();i++){
		vector<double> newFila;
		newFila.reserve(tuplas[i].size()+2);
		newFila.push_back(vectoresDir[i][0]);
		newFila.push_back(vectoresDir[i][1]);
		for(int j=0;j<tuplas[i].size();j++){
			newFila.push_back(tuplas[i][j]);
		}
		newTuplas.push_back(newFila);
	}
	return newTuplas;
}

vector<vector<int> > tomarVectoresDirectores(vector<vector<double> >& tuplas){
	vector<vector<int> > vectoresDir;
	vector<vector<double> > newTuplas;
	for(int i=0;i<tuplas.size();i++){
		vector<int> newDir(2,0);
		newDir[0]=tuplas[i][0];
		newDir[1]=tuplas[i][1];
		vectoresDir.push_back(newDir);
		vector<double> newFila;
		newFila.reserve(tuplas[i].size()-2);
		for(int j=2;j<tuplas[i].size();j++){
			newFila.push_back(tuplas[i][j]);
		}
		newTuplas.push_back(newFila);
	}
	tuplas=newTuplas;
	return vectoresDir;
}

void ComprimirVideo::comprimirFotograma(vector<vector<int> >& anterior, vector<vector<int> >& actual, string path){
	BlockMatching bm(anterior, actual);
	vector<vector<int> > vectoresDir=bm.blockMatching();
	vector<vector<int> > blockMatchedImage=bm.buildBlockMatchedImage(vectoresDir, anterior);
	vector<vector<double> > matrizImagen = actual-blockMatchedImage;
	vector<vector<double> > tuplass=TransCoseno::comprimirImagen(matrizImagen, 12);
	vector<vector<double> > newtuplas=agregarVectoresDirectores(tuplass, vectoresDir);
	CompressorFile cf((int)matrizImagen.size(),(int)matrizImagen[0].size(), 8.0, newtuplas);
	cf.CreateFile(path);
	cf.createImage(matrizImagen);	
}

vector<vector<double> > ComprimirVideo::descomprimirFotograma(int w, int h, vector<vector<double> >& tuplasorig, vector<vector<double> >& anterior){	
	vector<vector<int> > vectoresDirectores=tomarVectoresDirectores(tuplasorig);
	vector<vector<int> > blockMatchedImage=BlockMatching::buildBlockMatchedImage(vectoresDirectores, anterior);
	vector<vector<double> > Imagen=TransCoseno::descomprimirImagen(w,h,tuplasorig);
	vector<vector<double> > matrizImagen=Imagen+blockMatchedImage;
	return matrizImagen;
}
