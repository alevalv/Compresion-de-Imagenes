#include <vector>
using namespace std;

class TransCoseno {
private :
    vector< vector<int> > MatrizEntrada;
    vector< vector<int> > A;
    vector< vector<int> > Atranspuesta;
    
public :
    TransCoseno();
    void TransformarMatrizA();
    void AsignarMatrizAtranspuesta();
    ~TransCoseno();
};

#endif // TransCoseno_H
