#include "BlockMatching.h"
#include <math.h>
#include <vector>
#include <iostream>

using namespace std;

BlockMatching::BlockMatching(vector<vector<int> > anterior, vector<vector<int> > actual) : Anterior(anterior), Actual(actual){
}

vector<vector<double> > operator-(const vector<vector<double> >& a, const vector<vector<double> >& b){
	int w=a.size(), h=a[0].size();
	vector<vector<double> > resultado(w, vector<double>(h, 0));
	for(int i=0;i<w;i++)
	    for(int j=0;j<h;j++)
		resultado[i][j]=a[i][j]-b[i][j];
	return resultado;
}

bool BlockMatching::esValida(int i, int j){
	if(((i<0)||(i>Actual.size()))||((j<0)||(j>Actual[0].size()))){
		return false;
	}
	else return true;
}

vector<int> BlockMatching::buscarBloque(int i, int j){
	int ifound=-1, jfound=-1;
	vector<vector<double> > cuadroActual(8, vector<double>(8,0));
	vector<vector<double> > cuadroAnterior(8, vector<double>(8,0));
	double mse=1e20;
	for(int a=0;a<8;a++){
		for(int b=0;b<8;b++){
			cuadroActual[a][b]=Actual[i+a][j+b];
		}
	}
	do{	
		ifound=-1;
		jfound=-1;
		if(esValida(i, j)){
			for(int a=0;a<8;a++){
				for(int b=0;b<8;b++){
					cuadroAnterior[a][b]=Anterior[i+a][j+b];
				}
			}
			double newMSE=MSE(cuadroActual, cuadroAnterior);
			cerr<<"valido 1: "<<newMSE<<endl;
			if(newMSE<mse){
			cerr<<"valido 1: "<<newMSE<<endl;
				mse=newMSE;
				jfound=j;
				ifound=i;
			}
		}
		if(esValida(i, j-8)){
			for(int a=0;a<8;a++){
				for(int b=0;b<8;b++){
					cuadroAnterior[a][b]=Anterior[i+a][j+b-8];
				}
			}
			double newMSE=MSE(cuadroActual, cuadroAnterior);
			cerr<<"valido 2: "<<newMSE<<endl;
			if(newMSE<mse){
			cerr<<"valido 2: "<<newMSE<<endl;
				mse=newMSE;
				jfound=j-8;
				ifound=i;
			}
		}
		if(esValida(i-8, j)){
			for(int a=0;a<8;a++){
				for(int b=0;b<8;b++){
					cuadroAnterior[a][b]=Anterior[i+a-8][j+b];
				}
			}
			double newMSE=MSE(cuadroActual, cuadroAnterior);
			cerr<<"valido 3: "<<newMSE<<endl;
			if(newMSE<mse){
			cerr<<"valido 3: "<<newMSE<<endl;
				mse=newMSE;
				jfound=j;
				ifound=i-8;
			}
		}
		if(esValida(i, j+8)){
			for(int a=0;a<8;a++){
				for(int b=0;b<8;b++){
					cuadroAnterior[a][b]=Anterior[i+a][j+b+8];
				}
			}
			double newMSE=MSE(cuadroActual, cuadroAnterior);
			cerr<<"valido 4: "<<newMSE<<endl;
			if(newMSE<mse){
			cerr<<"valido 4: "<<newMSE<<endl;
				mse=newMSE;
				jfound=j+8;
				ifound=i;
			}
		}
		if(esValida(i+8, j)){
			for(int a=0;a<8;a++){
				for(int b=0;b<8;b++){
					cuadroAnterior[a][b]=Anterior[i+a+8][j+b];
				}
			}
			double newMSE=MSE(cuadroActual, cuadroAnterior);
			cerr<<"valido 5: "<<newMSE<<endl;
			if(newMSE<mse){
			cerr<<"valido 5: "<<newMSE<<endl;
				mse=newMSE;
				jfound=j;
				ifound=i+8;
			}
		}
		if((ifound!=-1)&&(jfound!=-1)){
			i=ifound;
			j=jfound;
		}
	}while((ifound!=-1) &&(jfound!=-1) );
	vector<int> salida(2,0);
	salida[0]=i;
	salida[1]=j;
	return salida;
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


