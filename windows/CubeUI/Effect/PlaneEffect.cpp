#include <iostream>
#include "PlaneEffect.h"

using namespace std;
using namespace NX;

void PlaneEffect::run() {
	clearAll();
	// Front
	setPlaneX(mRunner);
	setPlaneY(mRunner);
	setPlaneZ(mRunner);
	setPlaneX(7 - mRunner);
	setPlaneY(7 - mRunner);
	setPlaneZ(7 - mRunner);
	mRunner = (mRunner + 1) % 8;
}