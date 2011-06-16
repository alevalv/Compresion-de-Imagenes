
#include <iostream>
#include <vector>
#include "TransCoseno.h"

using namespace std;

int main(){
	vector<vector<double> > entrada(4, vector<double>(4, 0));
	int a=0;
	for(int i=0;i<entrada.size();i++){
		for(int j=0;j<entrada[0].size();j++){
			entrada[i][j]=a;
			a++;
		}
	}
	TransCoseno b;
	vector<double> salida=b.recorridoZigZag(entrada);
	for(int i=0;i<salida.size();i++){
		cout<<salida[i]<<endl;
	}
}
