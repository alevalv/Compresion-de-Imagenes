#ifndef COMPRIMIRVIDEO_H_
#define COMPRIMIRVIDEO_H_
#include <vector>
#include <string>
using namespace std;

class ComprimirVideo {
private :
     	string prefijo;
     	int IMAGE_NUMBER;
public :
	ComprimirVideo(string, int);
	void comprimirImagenes();
	void comprimirFotograma(vector<vector<double> >&, vector<vector<double> >&, string);
};

#endif // COMPRIMIRVIDEO_H
