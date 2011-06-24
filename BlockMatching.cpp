#include "BlockMatching.h"
#include <math.h>
#include <vector>
#include <iostream>
#include <cassert>
using namespace std;

BlockMatching::BlockMatching(vector<vector<int> >& Anterior, vector<vector<int> >& Actual){
	assert(Anterior.size()==Actual.size());
	assert(Anterior[0].size()==Actual[0].size());
	this->Anterior=Anterior;
	this->Actual=Actual;
}

bool BlockMatching::esValida(int i, int j){
	if((i<0)||(i>(Actual.size()-8))||(j<0)||(j>(Actual[0].size()-8))){
		return false;
	}
	else return true;
}

vector<vector<int> > BlockMatching::blockMatching(){
	int width=Anterior.size();
	int height=Anterior[0].size();
	vector<vector<int> > dirVectors;
	dirVectors.reserve((width*height)/8);
	for(int i=0;i<width;i+=8){
		for(int j=0;j<height;j+=8){
			dirVectors.push_back(buscarBloque(i,j));
		}
	}
	return dirVectors;
}

vector<int> BlockMatching::buscarBloque(int i, int j){
	//cerr<<endl<<"bloque "<<i<<" "<<j<<endl;
	int ifound=-1, jfound=-1;
	vector<vector<double> > cuadroActual(8, vector<double>(8,0));
	vector<vector<double> > cuadroAnterior(8, vector<double>(8,0));
	double mse=1e20;
	for(int a=0;a<8;a++){
		for(int b=0;b<8;b++){
			cuadroActual[a][b]=Actual[i+a][j+b];
		}
	}
	for(int a=0;a<8;a++){
			for(int b=0;b<8;b++){
				cuadroAnterior[a][b]=Anterior[i+a][j+b];
			}
		}
	mse=MSE(cuadroActual, cuadroAnterior);
	//cerr<<"ca"<<endl;
	int jumps=0;
	do{	
		ifound=-1;
		jfound=-1;
		//cerr<<"p1"<<endl;
		for(int c=-8;c<=8;c++){
			for(int d=-8;d<=8;d++){
				if(esValida(i+c,j+d)){
					for(int a=0;a<8;a++){
						for(int b=0;b<8;b++){
							cuadroAnterior[a][b]=Anterior[i+c+a][j+d+b];
						}
					}
					double newMSE=MSE(cuadroActual, cuadroAnterior);
					if(newMSE<mse){
						mse=newMSE;
						ifound=i+c;
						jfound=j+d;
					}
				}
			}
		}
		if((ifound!=-1)&&(jfound!=-1)){
			jumps++;
			i=ifound;
			j=jfound;
		}
	}while((ifound!=-1) &&(jfound!=-1) && (jumps<6));
	vector<int> salida(2,0);
	salida[0]=i;
	salida[1]=j;
	return salida;
}

vector<vector<int> > BlockMatching::buildBlockMatchedImage(vector<vector<int> >& dirVect, vector<vector<int> >& oldImage){
	vector<vector<int> > blockMatchedImage;
	int width=oldImage.size();
	int height=oldImage[0].size();
	blockMatchedImage.reserve(width);
	for(int i=0;i<width;i++){
		vector<int> newFila(height, 0);
		blockMatchedImage.push_back(newFila);
	}
	cerr<<dirVect.size()<<endl;
	int vectorActual=0;
	for(int i=0;i<width;i+=8){
		for(int j=0;j<height;j+=8){
			for(int a=0;a<8;a++){
				for(int b=0;b<8;b++){
					blockMatchedImage[i+a][j+b]=oldImage[dirVect[vectorActual][0]+a][dirVect[vectorActual][1]+b];
				}
			}
			vectorActual++;
		}
	}
	return blockMatchedImage;
}

vector<vector<int> > BlockMatching::buildBlockMatchedImage(vector<vector<int> >& dirVect, vector<vector<double> >& oldImage){
	vector<vector<int> > blockMatchedImage;
	int width=oldImage.size();
	int height=oldImage[0].size();
	blockMatchedImage.reserve(width);
	for(int i=0;i<width;i++){
		vector<int> newFila(height, 0);
		blockMatchedImage.push_back(newFila);
	}
	cerr<<dirVect.size()<<endl;
	int vectorActual=0;
	for(int i=0;i<width;i+=8){
		for(int j=0;j<height;j+=8){
			for(int a=0;a<8;a++){
				for(int b=0;b<8;b++){
					blockMatchedImage[i+a][j+b]=(int)oldImage[dirVect[vectorActual][0]+a][dirVect[vectorActual][1]+b];
				}
			}
			vectorActual++;
		}
	}
	return blockMatchedImage;
}

double BlockMatching::MSE(const vector< vector<double> >& Original,const vector< vector<double> >& Descomprimida){
	int cols=Original.size(), raws=Original.at(0).size();
	double mse=0;	
 	for(int i=0; i<cols; i++){
		for(int j=0; j<raws; j++){
			mse+=pow(Original.at(i).at(j)-Descomprimida.at(i).at(j),2);
			}
		}
     mse/=pow(cols*raws,2);
     return mse;
}
