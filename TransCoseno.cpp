#include <vector>
#include <math.h>
#include <iostream>
#include "TransCoseno.h"

using namespace std;

/**
* Esta función ha sido tomada de http://rosettacode.org/wiki/Zig-zag_matrix#Java
* y llevada a c++, además se cambiaron algunas cosas internas.
*/
vector<double> TransCoseno::recorridoZigZag(const vector<vector<double> >& data){
	 int size=data.size();
	 int i = 1;
	 int j = 1;
	 vector<double> salida;
	 salida.reserve(size*size);
	 for (int element = 0; element < size * size; element++)
	 {
	  salida.push_back(data[i - 1][j - 1]);
	  if ((i + j) % 2 == 0)
	  {
	   // Odd stripes
	   if (i < size)
		i++;
	   else
		j+= 2;
	   if (j > 1)
		j--;
	  }
	  else
	  {

	   // Even stripes
	   if (j < size)
		j++;
	   else
		i+= 2;
	   if (i > 1)
		i--;
	  }
	 }
	 return salida;
}

vector<vector<double> > operator*(const vector<vector<double> >& a, const vector<vector<double> >& b){
	int w1=a.size(), w2=b.size(), h2=b[0].size();
	vector<vector<double> > resultado(w1, vector<double>(h2, 0));
	for(int i=0;i<w1;i++){
		for(int j=0;j<h2;j++){
			for(int k=0;k<w2;k++){
				resultado[i][j]+=a[i][k]*b[k][j];
			}
		}
	}
	return resultado;
}


TransCoseno::TransCoseno(vector< vector<double> >& matrizEntrada) : MatrizEntrada(matrizEntrada){
	this->HEIGHT=matrizEntrada.size();
	this->WIDTH=matrizEntrada[0].size();
	this->N=HEIGHT*WIDTH;
}

/*
void TransCoseno::TransformarMatrizA(){
     A.resize(8,vector<double>(8,0));
     int rows=HEIGHT, cols=WIDTH;
     //double N=64;//SUPONGAMOS QUE SEA LA DIMENSION DE LA MATRIZ, ESTE VALOR ES DE PRUEBA
     double pi=3.14159265358979323846264338327950288419716939937510;
     double c=sqrt(1/N); //ESTO PASA CUANDO I=0
     
     for(int j=0;j<cols;j++)
           A[0][j]=c;
           
     c=sqrt(2/N);//ESTO PASA CUANDO I>0;     
     
     for(int i=1;i<rows;i++)
        for(int j=0;j<cols;j++)
            A[i][j]=c*cos(((2*j+1)*i*pi)/(2*N));
}
*/
vector<vector<double> > TransCoseno::generateA(int dimension){
     vector<vector<double> > salida(dimension,vector<double>(dimension,0));
     int rows=dimension, cols=dimension;
     double N=dimension;//SUPONGAMOS QUE SEA LA DIMENSION DE LA MATRIZ, ESTE VALOR ES DE PRUEBA
     double pi=3.14159265358979323846264338327950288419716939937510;
     double c=sqrt(1/N); //ESTO PASA CUANDO I=0
     
     for(int j=0;j<cols;j++)
           salida[0][j]=c;
           
     c=sqrt(2/N);//ESTO PASA CUANDO I>0;     
     
     for(int i=1;i<rows;i++)
        for(int j=0;j<cols;j++)
            salida[i][j]=c*cos(((2*j+1)*i*pi)/(2*N));
     return salida;
}

/*
void TransCoseno::AsignarMatrizAtranspuesta(){
    int rows=A.size(), cols=A.at(0).size(); 
    Atranspuesta.resize(cols,vector<double>(rows,0));  
    
    for(int i=0;i<rows;i++){
            for(int j=0;j<cols;j++){
              Atranspuesta[j][i]=A[i][j];
            }
    }
}
*/

vector<vector<double> > TransCoseno::transposeMatrix(const vector<vector<double> >& mtrx){
    int rows=mtrx.size(), cols=mtrx[0].size(); 
    vector<vector<double> > mtrxT(cols,vector<double>(rows,0));  
    
    for(int i=0;i<rows;i++){
            for(int j=0;j<cols;j++){
              mtrxT[j][i]=mtrx[i][j];
            }
    }
    return mtrxT;
}


vector<vector<double> > TransCoseno::generateQP(int dimension){
	vector< vector<double> > QP(dimension, vector<double>(dimension, 12));
	return QP;
}

void TransCoseno::aplicarQP(vector<vector<double> >& X, const vector<vector<double> >& QP){
	 int w=X.size(), h=X.at(0).size();
	 cout<<w<<" "<<h<<endl;
	 vector<vector<double> > FQ(w,vector<double>(h,0));
	 for(int i=0;i<w;i++){
		for(int j=0;j<h;j++){
			FQ[i][j]=floor((X[i][j]/QP[i][j])+0.5);
			X[i][j]=FQ[i][j]*QP[i][j];
		}  
	 }
 }
 
vector<vector<double> > TransCoseno::aplicarTransformada(const vector<vector<double> >& A,
										const vector<vector<double> >& AT){	
	return A*MatrizEntrada*AT;

}

TransCoseno::~TransCoseno(){
}
