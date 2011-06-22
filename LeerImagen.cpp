#include <fstream>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <sstream>
#include <cassert>
#include <math.h>

#include "LeerImagen.h"
using namespace std;



LeerImagen::LeerImagen(string NameFile){
	 
	
         string index, comment, cols, raws, maxbit;
	 int Cols, Raws, MaxBit;
         ifstream FileIn(NameFile.c_str(), ios::in);

         if(!FileIn.is_open()){
                                  cerr<<"no se pudo abrir el archivo "<<NameFile<<" :("<<endl;

                                  }
         getline(FileIn, index);
         getline(FileIn, comment);

         while(comment[0]=='#')
             getline(FileIn,comment);

         istringstream tokenizer(comment);
         tokenizer>>cols>>raws;
         FileIn >> maxbit;
         assert( maxbit=="255" );


        Cols=atoi(cols.c_str());
        Raws=atoi(raws.c_str());
        MaxBit=atoi(maxbit.c_str());

	 assert( (Cols%8)==0 );
         assert( (Raws%8)==0 );
         //Creation de las matrices

         Matriz.resize(Cols,vector<int>(Raws,0));
	

       if (index=="P3"){


         vector< vector <int> > Red(Cols,vector<int>(Raws,0));
         vector< vector <int> > Green(Cols,vector<int>(Raws,0));
         vector< vector <int> > Blue(Cols,vector<int>(Raws,0));

        for(int i=0;i<Raws;i++){
             for(int j=0;j<Cols;j++){
                       FileIn >> Red[j][i];
                       FileIn >> Green[j][i];
                       FileIn >> Blue[j][i];
                         }
                                     }


            for(int i=0;i<Raws;i++){
                  for(int j=0;j<Cols;j++){
                      Matriz.at(j).at(i)=RGBtoGray(Red[j][i],Green[j][i],Blue[j][i]);

                                                 }
                                         }

            }

     else{

         for(int i=0;i<Raws;i++){
               for(int j=0;j<Cols;j++){
                   FileIn >>Matriz[j][i];

                }
           }
     }

     FileIn.close();

    

     
}


int LeerImagen::RGBtoGray(int r, int g, int b){
    return  r*0.299+g*0.587+b*0.114;
}


vector< vector<int> > LeerImagen::getMatriz(){
	
    return Matriz;
}
