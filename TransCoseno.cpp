#include <vector>
#include <math.h>
#include <iostream>
#include "TransCoseno.h"

using namespace std;





TransCoseno::TransCoseno(vector< vector<double> >& matrizEntrada) : MatrizEntrada(matrizEntrada){
	this->HEIGHT=matrizEntrada.size();
	this->WIDTH=matrizEntrada[0].size();
	this->N=HEIGHT*WIDTH;
}

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

 vector<vector<double> > TransCoseno::recorridoZigZagInvertido(const vector<double>& data){
	 int size=sqrt(data.size());
	 int i = 1;
	 int j = 1;
	 vector<vector<double> > salida;
	 salida.reserve(size);
	 for(int i=0;i<size;i++){
		 vector<double> a(size, 0);
		 salida.push_back(a);
	 }
	 for (int element = 0; element < data.size(); element++)
	 {
	  salida[i - 1][j - 1]=data[element];
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


vector<double> TransCoseno::generarTuplas(const vector<double>& data){
	int conteo=0, actual;
	vector<double> tuplas;
	tuplas.reserve(data.size());
	for(int i=0;i<(int)data.size();i++){
		actual=data[i];
		if(actual==0){
			conteo++;
			continue;
		}
		else{
			tuplas.push_back(conteo);
			tuplas.push_back(actual);
			conteo=0;
		}
	}
	return tuplas;
}

vector<double> TransCoseno::inversaTuplas(const vector<double>& data){
	vector<double> zigzag;
	int MAX_SIZE=64;
	zigzag.reserve(MAX_SIZE);
	int i;
	for(i=0;i<(int)data.size();i=i+2){
		int zero_count=data[i];
		while(zero_count>0){
			zigzag.push_back(0.0);
			zero_count--;			
		}
		zigzag.push_back(data[i+1]);
	}
	while(i<=MAX_SIZE){
		zigzag.push_back(0.0);
		i++;
	}
	return zigzag;
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

vector<vector<double> > TransCoseno::aplicarTransformada(const vector<vector<double> >& A,
										const vector<vector<double> >& AT){	
	return A*MatrizEntrada*AT;

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
 


TransCoseno::~TransCoseno(){
}
