#ifndef TRANSCOSENO_H_
#define TRANSCOSENO_H_
#include <vector>

using namespace std;

class TransCoseno {
private :
    vector< vector<int> > MatrizEntrada;
    vector< vector<double> > A;
    vector< vector<double> > Atranspuesta;
    
public :
    TransCoseno(vector< vector<int> >&);
    TransCoseno();
    void TransformarMatrizA();
    void AsignarMatrizAtranspuesta();
    vector<double> recorridoZigZag(const vector<vector<double> >&);	
    ~TransCoseno();
};

#endif // TRANSCOSENO_H
