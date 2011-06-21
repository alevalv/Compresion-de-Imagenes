#ifndef LEERIMAGEN_H
#define LEERIMAGEN_H

#include <string>
#include <vector>
using namespace std;

class LeerImagen {
private :
    vector< vector<int> > Matriz;
    vector<vector<vector<double> > > Fragmentos;

public :
    LeerImagen(string);
    void FragmentarImagen();
    int RGBtoGray(int r, int g, int b);
    vector< vector<int> > getMatriz(); 
};

#endif // LEERIMAGEN_H
