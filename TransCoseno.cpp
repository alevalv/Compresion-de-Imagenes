#include <vector>
#include <math.h>
#include <iostream>
#include <cassert>
#include "TransCoseno.h"

using namespace std;





TransCoseno::TransCoseno(){
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
	 int size=8;
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
	while(zigzag.size()<MAX_SIZE){
		zigzag.push_back(0.0);
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
										const vector<vector<double> >& ME,
										const vector<vector<double> >& AT){	
	return A*ME*AT;

}

vector<vector<double> > TransCoseno::aplicarTransformadaInversa(const vector<vector<double> >& A,
										const vector<vector<double> >& ME,
										const vector<vector<double> >& AT){	
	return AT*ME*A;

}


vector<vector<double> > TransCoseno::generateQP(int value){
	if(value!=-1){
		vector< vector<double> > QP(8, vector<double>(8, value));
		return QP;
	}
	else{
		vector< vector<double> > QP(8, vector<double>(8, 0));
		QP[0][0]=16;
		QP[0][1]=11;
		QP[0][2]=10;
		QP[0][3]=16;
		QP[0][4]=24;
		QP[0][5]=40;
		QP[0][6]=51;
		QP[0][7]=61;
		QP[1][0]=12;
		QP[1][1]=12;
		QP[1][2]=14;
		QP[1][3]=19;
		QP[1][4]=26;
		QP[1][5]=58;
		QP[1][6]=60;
		QP[1][7]=55;
		QP[2][0]=14;
		QP[2][1]=13;
		QP[2][2]=16;
		QP[2][3]=24;
		QP[2][4]=40;
		QP[2][5]=57;
		QP[2][6]=69;
		QP[2][7]=56;
		QP[3][0]=14;
		QP[3][1]=17;
		QP[3][2]=22;
		QP[3][3]=29;
		QP[3][4]=51;
		QP[3][5]=87;
		QP[3][6]=80;
		QP[3][7]=62;
		QP[4][0]=18;
		QP[4][1]=22;
		QP[4][2]=37;
		QP[4][3]=56;
		QP[4][4]=68;
		QP[4][5]=109;
		QP[4][6]=103;
		QP[4][7]=77;
		QP[5][0]=24;
		QP[5][1]=35;
		QP[5][2]=55;
		QP[5][3]=64;
		QP[5][4]=81;
		QP[5][5]=104;
		QP[5][6]=113;
		QP[5][7]=92;
		QP[6][0]=49;
		QP[6][1]=64;
		QP[6][2]=78;
		QP[6][3]=87;
		QP[6][4]=103;
		QP[6][5]=121;
		QP[6][6]=120;
		QP[6][7]=101;
		QP[7][0]=72;
		QP[7][1]=92;
		QP[7][2]=95;
		QP[7][3]=98;
		QP[7][4]=112;
		QP[7][5]=100;
		QP[7][6]=103;
		QP[7][7]=99;
		return QP;
	}
	
}

void TransCoseno::aplicarQP(vector<vector<double> >& X, const vector<vector<double> >& QP){
	 int w=X.size(), h=X.at(0).size();
	 //cout<<w<<" "<<h<<endl;
	 vector<vector<double> > FQ(w,vector<double>(h,0));
	 for(int i=0;i<w;i++){
		for(int j=0;j<h;j++){
			FQ[i][j]=floor((X[i][j]/QP[i][j])+0.5);
			X[i][j]=FQ[i][j]*QP[i][j];
		}  
	 }
 }
 
vector<vector<double> > TransCoseno::comprimirImagen(vector<vector<int> >& matriz, int qpGen){
	vector<vector<double> > tuplas;
	vector<vector<double> > cuadroActual;
	vector<vector<double> > A=generateA(8);
	vector<vector<double> > AT=transposeMatrix(A);
	vector<vector<double> > QP=generateQP(qpGen);
	for(int i=0;i<matriz.size();i=i+8){
		for(int j=0;j<matriz[i].size();j=j+8){
			
			//obtenemos el cuadro actual
			for(int a=0;a<8;a++){
				vector<double> filaActual;
				filaActual.reserve(8);
				for(int b=0;b<8;b++){
					filaActual.push_back(matriz[i+a][j+b]);
				}
				cuadroActual.push_back(filaActual);
			}
			vector<vector<double> > transformadaCoseno=aplicarTransformada(A, cuadroActual, AT);
			aplicarQP(transformadaCoseno, QP);
			tuplas.push_back(generarTuplas(recorridoZigZag(transformadaCoseno)));
			cuadroActual.clear();
			transformadaCoseno.clear();
		}
	}
	cerr<<"se generaron "<<tuplas.size()<<" tuplas"<<endl;
	return tuplas;
}

vector<vector<double> > TransCoseno::comprimirImagen(vector<vector<double> >& matriz, int qpGen){
	vector<vector<double> > tuplas;
	vector<vector<double> > cuadroActual;
	vector<vector<double> > A=generateA(8);
	vector<vector<double> > AT=transposeMatrix(A);
	vector<vector<double> > QP=generateQP(qpGen);
	for(int i=0;i<matriz.size();i=i+8){
		for(int j=0;j<matriz[i].size();j=j+8){
			
			//obtenemos el cuadro actual
			for(int a=0;a<8;a++){
				vector<double> filaActual;
				filaActual.reserve(8);
				for(int b=0;b<8;b++){
					filaActual.push_back(matriz[i+a][j+b]);
				}
				cuadroActual.push_back(filaActual);
			}
			vector<vector<double> > transformadaCoseno=aplicarTransformada(A, cuadroActual, AT);
			aplicarQP(transformadaCoseno, QP);
			tuplas.push_back(generarTuplas(recorridoZigZag(transformadaCoseno)));
			cuadroActual.clear();
			transformadaCoseno.clear();
		}
	}
	cerr<<"se generaron "<<tuplas.size()<<" tuplas"<<endl;
	return tuplas;
}

vector<vector<double> > TransCoseno::descomprimirImagen(int width, int height, const vector< vector<double> >& Tuplas){///aqui se puede colocar que reciba un objeto compressorfile
	
	vector<vector<double> > MatrizImagen;
	for(int i=0;i<width;i++){
		vector<double> fila(height, 0);
		MatrizImagen.push_back(fila);
	}
	vector<double> zigzag;
	vector<vector<double> > A=generateA(8);
	vector<vector<double> > AT=transposeMatrix(A);
  	int tuplaActual=0;	
   	for(int i=0;i<width;i+=8){
		for(int j=0;j<height;j+=8){			
			vector<vector<double> > cuadroActual=aplicarTransformadaInversa(A, recorridoZigZagInvertido(inversaTuplas(Tuplas[tuplaActual])), AT);			
			for(int a=0;a<8;a++){
				for(int b=0;b<8;b++){					
					MatrizImagen[i+a][j+b]=min(255.0, max(cuadroActual[a][b],0.0));
				}
			}
			cuadroActual.clear();
			tuplaActual++;
		}
	}
	return MatrizImagen;
}
/*
double TransCoseno::MSE(const vector< vector<double> >& Original,const vector< vector<double> >& Descomprimida){

	int cols=Original.size(), raws=Original.at(0).size();
		
	double mse=0;	
 	for(int i=0; i<cols; i++){
		for(int j=0; j<raws; j++){
			mse+=pow(Original.at(i).at(j)-Descomprimida.at(i).at(j),2);
			}


		}
     mse/=pow(cols*raws,2);
     return mse;

}*/

TransCoseno::~TransCoseno(){
}
