#ifndef COMPRIMIRVIDEO_H_
#define COMPRIMIRVIDEO_H_
#include <vector>

using namespace std;

class ComprimirVideo {
private :
     	string prefijo;
public :
	ComprimirVideo(vector<vector<int> >, vector<vector<int> >);
	void comprimirImagenes();
};

#endif // COMPRIMIRVIDEO_H
