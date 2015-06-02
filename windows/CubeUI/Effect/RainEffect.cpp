#include <iostream>
#include "RainEffect.h"

using namespace std;
using namespace NX;

void RainEffect::run() {
	clearAll();
	// Front
	list<int>::iterator xtr;
	list<int>::iterator ytr;
	list<int>::iterator ztr;

	xtr = xValues.begin();
	ytr = yValues.begin();
	ztr = zValues.begin();

	size_t size = xValues.size();
	if (size != yValues.size() || size != zValues.size())
		return;

	for (size_t i = 0; i < size; ++i) {
		int x, y, z;
		x = *xtr;
		y = *ytr;
		z = *ztr;

		setLed(x, y, z);

		xtr++;
		ytr++;
		ztr++;
	}

	ztr = zValues.begin();
	ytr = yValues.begin();
	xtr = xValues.begin();

	for (size_t i = 0; i < size; ++i) {
		int z = *ztr;
		z--;
		if (z == -1) {
			xValues.erase(xtr);
			yValues.erase(ytr);
			zValues.erase(ztr);

			xtr = xValues.begin();
			ytr = yValues.begin();
			ztr = zValues.begin();
		}
		else {
			*ztr = z;
			xtr++;
			ytr++;
			ztr++;
		}
	}

	for (size_t i = 0; i < 5; i++) {
		xValues.push_back(rand() % 8);
		yValues.push_back(rand() % 8);
		zValues.push_back(7);
	}
}