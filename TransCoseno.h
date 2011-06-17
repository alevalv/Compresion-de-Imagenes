#ifndef TRANSCOSENO_H_
#define TRANSCOSENO_H_
#include <vector>

using namespace std;

class TransCoseno {
private :
    vector< vector<double> > MatrizEntrada;
    vector< vector<double> > A;
    vector< vector<double> > Atranspuesta;
    int HEIGHT;
    int WIDTH;
    int N;
    
public :
    TransCoseno(vector< vector<double> >&);
    TransCoseno();
    void TransformarMatrizA();
    void AsignarMatrizAtranspuesta();
    vector<double> recorridoZigZag(const vector<vector<double> >&);	
    static vector<vector<double> > generateA(int);
    static vector<vector<double> > transposeMatrix(const vector<vector<double> >&);
	vector<vector<double> > aplicarTransformada();
    ~TransCoseno();
};

#endif // TRANSCOSENO_H
