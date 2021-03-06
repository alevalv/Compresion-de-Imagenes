#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include "CompressorFile.h"

using namespace std;

CompressorFile::CompressorFile(int width, int height, double QP, const vector< vector<double> >& Tuplas){

    this->Tuplas=Tuplas;
    this->QP=QP;
    this->width=width;
    this->height=height;

}

CompressorFile::CompressorFile(){
	
	};


void CompressorFile::CreateFile(string path){
   ofstream archivoOut(path.c_str(), ios::binary);
   cerr<<Tuplas.size()<<Tuplas[0].size()<<endl;
   if(!archivoOut.is_open()){
                            cerr<<"no se pudo abrir el archivo :O"<<endl;


                            }
   
   archivoOut<<"# Imagen comprimida por Cristina Bustos y Alejandro Valdes \n";
   archivoOut<<width<<" "<<height<<"\n";
   
   for(int i=0;i<(int)Tuplas.size();i++){
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
vector<vector<double> > CompressorFile::ReadCompressedFile(string path){
	ifstream FileIn(path.c_str(), ios::in);
    if(!FileIn.is_open()){
		cerr<<"no se pudo abrir el archivo "<<path<<" :("<<endl;
    }

    string header, temp, Width, Height;
    vector<vector<double> > tuplas;
    vector<double> temporal;
    getline(FileIn, header);
    getline(FileIn, temp);
     
    istringstream tokenizer1(temp);
    tokenizer1>>Width>>Height;
    width=atoi(Width.c_str());
    height=atoi(Height.c_str());

    string tuplita="";        
    do{
		getline(FileIn, temp);
		istringstream tokenizer(temp);
        tokenizer>>tuplita;
        while(tokenizer!=NULL){
			temporal.push_back(atof(tuplita.c_str()));   
			tokenizer>>tuplita;	
        }
        tuplas.push_back(temporal);
		temporal.clear();
    }while(!FileIn.eof());
  /*  cout<<"Lectura del Archivo  \n";
	cout<<"header "<<header<<"\n";
	cout<<"ancho "<<Width<<"\n";	
	cout<<"largo "<<Heigth<<"\n";
	cout<<"qp "<<qp<<"\n";
	
	for(int i=0;i<tuplas.size();i++){
		for(int j=0;j<tuplas[i].size();j++)
			cout<<tuplas[i][j]<<" ";		
		cout<<"\n";
	}*/

	return tuplas;
}

int CompressorFile::getWidth(){

    return width;
}

int CompressorFile::getHeight(){

    return height;
}

void CompressorFile::CreateImagenDescomprimida(vector<vector<double> >& Matriz, string path){
   ofstream archivoOut(path.c_str(), ios::binary);
   if(!archivoOut.is_open()){
                            cerr<<"no se pudo abrir el archivo :O"<<endl;

                            }
   int Cols=Matriz.size(), Raws=Matriz.at(0).size();
   archivoOut<<"P2\n";
   archivoOut<<Cols<<" "<<Raws<<"\n";
   archivoOut<<"255\n";

   for(int i=0;i<Raws;i++){
         for(int j=0;j<Cols;j++){
             archivoOut <<(int)Matriz[j][i];
             archivoOut<<"\n";
                             }

                                }
    archivoOut.close();
    cout << "El archivo ha sido guardado exitosamente en "<<path<<" ;)"<<endl;
}

void CompressorFile::createImage(vector<vector<int> >& Matriz){
	string path="DEBUG.pgm";
   ofstream archivoOut(path.c_str(), ios::binary);
   if(!archivoOut.is_open()){
                            cerr<<"no se pudo abrir el archivo :O"<<endl;

                            }
   int Cols=Matriz.size(), Raws=Matriz.at(0).size();
   archivoOut<<"P2\n";
   archivoOut<<Cols<<" "<<Raws<<"\n";
   archivoOut<<"255\n";

   for(int i=0;i<Raws;i++){
         for(int j=0;j<Cols;j++){
             archivoOut <<(int)Matriz[j][i];
             archivoOut<<"\n";
                             }

                                }
    archivoOut.close();
    cout << "El archivo ha sido guardado exitosamente en "<<path<<" ;)"<<endl;
}

void CompressorFile::createImage(vector<vector<double> >& Matriz){
	string path="DEBUG.pgm";
   ofstream archivoOut(path.c_str(), ios::binary);
   if(!archivoOut.is_open()){
                            cerr<<"no se pudo abrir el archivo :O"<<endl;

                            }
   int Cols=Matriz.size(), Raws=Matriz.at(0).size();
   archivoOut<<"P2\n";
   archivoOut<<Cols<<" "<<Raws<<"\n";
   archivoOut<<"255\n";

   for(int i=0;i<Raws;i++){
         for(int j=0;j<Cols;j++){
             archivoOut <<max(min(255, (int)(Matriz[j][i]+128)),0);
             archivoOut<<"\n";
                             }

                                }
    archivoOut.close();
    cout << "El archivo ha sido guardado exitosamente en "<<path<<" ;)"<<endl;
}
