#include <vector>
#include <math.h>
#include "TransCoseno.h"
using namespace std;

TransCoseno::TransCoseno(vector< vector<int> >& MatrizEntrada){
    this.MatrizEntrada=MatrizEntrada;
}

void TransCoseno::TransformarMatrizA(){
     A.resize(8,vector<int>(8,0));
     int rows=A.size(), cols=A.at(0).size();
     double N=64;//SUPONGAMOS QUE SEA LA DIMENSION DE LA MATRIZ, ESTE VALOR ES DE PRUEBA
     double pi=3.14159265358979323846264338327950288419716939937510;
     double c=sqrt(1/N); //ESTO PASA CUANDO I=0
     
     for(int j=0;j<cols;j++)
           A.at(0).at(j)=c*cos(((2*j+1)*0*pi)/(2*N));
           
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
