#include <vector>
#include "CompressorFile.h"

using namespace std;

CompressorFile::CompressorFile(int width, int height, double QP, const vector< vector<double> >& Tuplas){

    this->Tuplas=Tuplas;
    this->QP=QP;
    this->width=width;
    this->height=height;

}
