#ifndef FONTS_H
#define FONTS_H

#include "raylib.h"
using namespace std;

class Resources 
{
	int Spacings;
	int fontType;
	//const int fonts = 8;

public:
	Resources() { Spacings = 2; fontType = 1; }
	~Resources()	{}

	void setSpacings(int space) {
		Spacings = space;
	}

	void setType(int type) {
		fontType = type;
	}


	int getType() {
		return fontType;
	}


	int getSpacings() {
		return Spacings;
	}
	
};

#endif // !FONTS_H
