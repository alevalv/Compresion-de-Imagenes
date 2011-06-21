#include <vector>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include "CompressorFile.h"

using namespace std;

CompressorFile::CompressorFile(int width, int height, double QP, const vector< vector<double> >& Tuplas){

    this->Tuplas=Tuplas;
    this->QP=QP;
    this->width=width;
    this->height=height;

}

string CompressorFile::TuplatoString(const vector<double>& tupla){
	string result="";
	int temp=0;
	for(int i=0;i<tupla.size();i++){
		temp=(int)tupla[i];
		result+=temp;
		result+=" ";
	}
	return result+"\n";
}

void CompressorFile::CreateFile(string path){
   ofstream archivoOut(path.c_str(), ios::binary);
   if(!archivoOut.is_open()){
                            cerr<<"no se pudo abrir el archivo :O"<<endl;


                            }
   
   archivoOut<<"# Imagen comprimida por Cristina Bustos y Alejandro Valdes \n";
   archivoOut<<width<<" "<<height<<"\n";
   archivoOut<<QP<<"\n";

   for(int i=0;i<Tuplas.size();i++){
		for(int j=0;j<Tuplas[i].size();j++){                
		archivoOut<<Tuplas[i][j];
		if(j!=(Tuplas[i].size()-1))
			archivoOut<<" ";
        }
		if(i!=(Tuplas.size()-1))
			archivoOut<<"\n";
                           }
    archivoOut.close();
    cout << "El archivo ha sido guardado exitosamente en "<<path<<" ;)"<<endl;
}


//hay que discutir si esta funcion se encuentre en esta clase
void CompressorFile::ReadCompressedFile(string path){
    
     ifstream FileIn(this->path.c_str(), ios::in);
     if(!FileIn.is_open()){
                                  cerr<<"no se pudo abrir el archivo "<<path<<" :("<<endl;

                                  }

     string header, temp, Width, Heigth, qp;
     vector<string> tuplas(5,"");
     getline(FileIn, header);
     getline(FileIn, temp);
     istringstream tokenizer(temp);
     tokenizer>>Width>>Heigth;
     getline(FileIn,qp);

}


