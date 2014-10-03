#include <iostream>
#include "MatrixEffect.h"

using namespace std;
using namespace NX;

void MatrixEffect::run() {
	clearAll();
	// Front
	setRowZ(7-mRunner, 0);
	setRowX(0, 7-mRunner);
	// Back
	setRowZ(mRunner, 7);
	setRowX(7, mRunner);
	// Top
	setRowX(7-mRunner, 7);
	setRowY(mRunner, 7);
	// Bottom
	setRowY(7 - mRunner, 0);
	setRowX(mRunner, 0);
	// Right
	setRowY(0, mRunner);
	setRowZ(7, mRunner);
	// Left
	setRowY(7, 7 - mRunner);
	setRowZ(0, 7 - mRunner);
	mRunner = (mRunner + 1) % 8;
}