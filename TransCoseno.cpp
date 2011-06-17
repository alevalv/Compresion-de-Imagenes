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

void multiplicacionMatrices(vector<vector<double> >& a, vector<vector<double> >& b, vector<vector<double> >& resultado){
	int w1=a.size(), h1=a[0].size(), w2=b.size(), h2=b[0].size();
	if(w2==h1){
		for(int i=0;i<w1;i++){
			for(int j=0;j<h2;j++){
				for(int k=0;k<w2;k++){
					resultado[i][j]+=a[i][k]*b[k][j];
				}
			}
		}
	}
	else{
		cerr<<"Matrices de tamaños distintos"<<endl;
	}
}

TransCoseno::TransCoseno(vector< vector<double> >& MatrizEntrada){
    this->MatrizEntrada=MatrizEntrada;
}

TransCoseno::TransCoseno(){
}

void TransCoseno::TransformarMatrizA(){
     A.resize(8,vector<double>(8,0));
     int rows=A.size(), cols=A.at(0).size();
     double N=64;//SUPONGAMOS QUE SEA LA DIMENSION DE LA MATRIZ, ESTE VALOR ES DE PRUEBA
     double pi=3.14159265358979323846264338327950288419716939937510;
     double c=sqrt(1/N); //ESTO PASA CUANDO I=0
     
     for(int j=0;j<cols;j++)
           A.at(0).at(j)=c;
           
     c=sqrt(2/N);//ESTO PASA CUANDO I>0;     
     
     for(int i=1;i<rows;i++)
        for(int j=0;j<cols;j++)
            A.at(i).at(j)=c*cos(((2*j+1)*i*pi)/(2*N));
     
}

void TransCoseno::AsignarMatrizAtranspuesta(){
    int rows=A.size(), cols=A.at(0).size(); 
    Atranspuesta.resize(cols,vector<double>(rows,0));  
    
    for(int i=0;i<rows;i++){
            for(int j=0;j<cols;j++){
              Atranspuesta.at(j).at(i)=A.at(j).at(i);
            }
    }
}

vector<vector<double> > TransCoseno::aplicarTransformada(){
	cout<<"Inicializar a"<<endl;
	this->TransformarMatrizA();
	cout<<"Inicializar aT"<<endl;
	this->AsignarMatrizAtranspuesta();
	vector<vector<double> > temp1(8, vector<double>(8,0));
	cout<<"Trying first mult"<<endl;
	multiplicacionMatrices(A, MatrizEntrada, temp1);
	vector<vector<double> > salida(8, vector<double>(8,0));
	cout<<"Trying second mult"<<endl;
	multiplicacionMatrices(temp1, Atranspuesta, salida);
	return salida;

}

TransCoseno::~TransCoseno(){
}
