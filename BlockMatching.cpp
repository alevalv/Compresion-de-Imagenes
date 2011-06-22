#include "BlockMatching.h"

using namespace std;

BlockMatching::BlockMatching(){

}

vector<vector<double> > operator-(const vector<vector<double> >& a, const vector<vector<double> >& b){
	int w=a.size(), h=a[0].size();
	vector<vector<double> > resultado(w1, vector<double>(h2, 0));
	for(int i=0;i<w;i++)
	    for(int j=0;j<h;j++)
		resultado[i][j]=a[i][j]-b[i][j];
	return resultado;
}
