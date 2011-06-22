#ifndef COMPRIMIRVIDEO_H_
#define COMPRIMIRVIDEO_H_
#include <vector>

using namespace std;

class ComprimirVideo {
private :
     	vector<vector<int> > Anterior;
    	vector<vector<int> > Actual;
public :
	ComprimirVideo(vector<vector<int> >, vector<vector<int> >);

};

#endif // COMPRIMIRVIDEO_H
