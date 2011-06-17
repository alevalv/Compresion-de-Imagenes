
#include <iostream>
#include <vector>
#include "TransCoseno.h"

//http://www.physics.utah.edu/~detar/lessons/c++/matrices/node4.html
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
	vector<vector<double> > salida=b.aplicarTransformada();
	for(int i=0;i<salida.size();i++){
		for(int j=0;j<salida[0].size();j++){
			cout<<salida[i][j];
			if(j!=(salida[0].size()-1))
				cout<<" ";
		}
		cout<<endl;
	}
}
