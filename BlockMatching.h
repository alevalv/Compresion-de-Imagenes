#ifndef BLOCKMATCHING_H_
#define BLOCKMATCHING_H_
#include <vector>

using namespace std;

class BlockMatching {
private :
     	vector<vector<int> > Anterior;
    	vector<vector<int> > Actual;
	bool esValida(int, int);
public :
	BlockMatching(vector<vector<int> >, vector<vector<int> >);
	vector<int> buscarBloque(int,int);
    	double MSE(const vector< vector<double> >&,const vector< vector<double> >&);

};

#endif // BLOCKMATCHING_H
