#include <vector>
#include <math.h>
#include <iostream>
#include "TransCoseno.h"

using namespace std;

vector<double> TransCoseno::recorridoZigZag(const vector<vector<double> >& entrada){
	int count=0;
	int MAX_SIZE_HEIGHT=entrada[0].size();
	int MAX_SIZE_WIDTH=entrada.size();
	vector<double> salida;
	salida.reserve(entrada.size()*entrada[0].size());
	while(count!=MAX_SIZE_HEIGHT){
		if(((count+1) % 2) == 0){
			//pares
			int j=0;
			for(int i=count;((i!=-1)&&(j<=count));i--){
				salida.push_back(entrada[i][j]);
				j++;
			}
			count++;
		}
		else{
			//impares
			int j=count;
			for(int i=0;((i<=count)&&(j!=.1));i++){				
				salida.push_back(entrada[i][j]);
				j--;
			}
			count++;
		}
	}
	while(count!=MAX_SIZE_WIDTH){
		if(((count+1) % 2) == 0){
			//pares
			int j=0;
			for(int i=count;((i!=-1)&&(j<=count));i--){
				salida.push_back(entrada[i][j]);
				j++;
			}
			count++;
		}
		else{
			//impares
			int j=count;
			for(int i=0;((i<=count)&&(j!=.1));i++){				
				salida.push_back(entrada[i][j]);
				j--;
			}
			count++;
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

TransCoseno::TransCoseno(vector< vector<int> >& MatrizEntrada){
    this->MatrizEntrada=MatrizEntrada;
}

TransCoseno::TransCoseno(){
}

void TransCoseno::TransformarMatrizA(){
     A.resize(8,vector<int>(8,0));
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
    Atranspuesta.resize(cols,vector<int>(rows,0));  
    
    for(int i=0;i<rows;i++){
            for(int j=0;j<cols;j++){
              Atranspuesta.at(j).at(i)=A.at(j).at(i);
            }
    }
}

TransCoseno::~TransCoseno(){
}
