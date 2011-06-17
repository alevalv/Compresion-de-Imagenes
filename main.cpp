
#include <iostream>
#include <vector>
#include "TransCoseno.h"

using namespace std;

int main(){
	vector<vector<double> > entrada(8, vector<double>(8, 0));
	int a=0;
	for(int i=0;i<(int)entrada.size();i++){
		for(int j=0;j<(int)entrada[0].size();j++){
			entrada[i][j]=a;
			a++;
		}
	}
	TransCoseno b(entrada);
	vector<vector<double> > A=TransCoseno::generateA(8);
	vector<vector<double> > AT=TransCoseno::transposeMatrix(A);
	vector<vector<double> > salida=b.aplicarTransformada(A, AT);
	for(int i=0;i<(int)salida.size();i++){
		for(int j=0;j<(int)salida[0].size();j++){
			cout<<salida[i][j];
			if(j!=(salida[0].size()-1))
				cout<<" ";
		}
		cout<<endl;
	}
	
	
	//para mostrar la matriz cuantificada por QP
	vector<vector<double> > QP=TransCoseno::generateQP(8);
	TransCoseno::aplicarQP(salida,QP);
	
	cout<<"cuanti\n";
	for(int i=0;i<(int)salida.size();i++){
		for(int j=0;j<(int)salida[0].size();j++){
			cout<<salida[i][j];
			if(j!=(salida[0].size()-1))
				cout<<" ";
		}
		cout<<endl;
	}
	
	cout<<"--------------------"<<endl;
	TransCoseno c(salida);
	vector<vector<double> > salida2=c.aplicarTransformada(AT, A);
	for(int i=0;i<(int)salida2.size();i++){
		for(int j=0;j<(int)salida2[0].size();j++){
			cout<<salida2[i][j];
			if(j!=(salida2[0].size()-1))
				cout<<" ";
		}
		cout<<endl;
	}
}
