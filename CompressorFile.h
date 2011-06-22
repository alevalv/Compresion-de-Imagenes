#ifndef COMPRESSORFILE_H_
#define COMPRESSORFILE_H_
#include <vector>

using namespace std;

class CompressorFile {
private :
    vector< vector<double> > Tuplas;
    double QP;
    int width;
    int height;  
    

    
public :
    CompressorFile(int, int, double, const vector< vector<double> >&);
    CompressorFile();
    void CreateFile(string);
    void ReadCompressedFile(string);
    //~CompressorFile();
};

#endif // COMPRESSORFILE_H
