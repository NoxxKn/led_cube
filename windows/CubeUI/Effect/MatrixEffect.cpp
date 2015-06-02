#include <iostream>
#include <Windows.h>
#include "MatrixEffect.h"

using namespace std;
using namespace NX;

void MatrixEffect::run() {
	clearAll();

	// Front
	setRowZ((7 - mRunner) - mEqualizer, mEqualizer, mEqualizer, 8 - mEqualizer);
	setRowX(mEqualizer, (7 - mRunner) - mEqualizer, mEqualizer, 8 - mEqualizer);
	// Back
	setRowZ(mRunner + mEqualizer, 7 - mEqualizer, mEqualizer, 8 - mEqualizer);
	setRowX(7 - mEqualizer, mRunner + mEqualizer, mEqualizer, 8 - mEqualizer);
	// Top
	setRowX((7 - mRunner) - mEqualizer, 7 - mEqualizer, mEqualizer, 8 - mEqualizer);
	setRowY(mRunner + mEqualizer, 7 - mEqualizer, mEqualizer, 8 - mEqualizer);
	// Bottom
	setRowY((7 - mRunner) - mEqualizer, mEqualizer, mEqualizer, 8 - mEqualizer);
	setRowX(mRunner + mEqualizer, mEqualizer, mEqualizer, 8 - mEqualizer);
	// Right
	setRowY(mEqualizer, mRunner + mEqualizer, mEqualizer, 8 - mEqualizer);
	setRowZ(7 - mEqualizer, mRunner + mEqualizer, mEqualizer, 8 - mEqualizer);
	// Left
	setRowY(7 - mEqualizer, (7 - mRunner) - mEqualizer, mEqualizer, 8 - mEqualizer);
	setRowZ(mEqualizer, (7 - mRunner) - mEqualizer, mEqualizer, 8 - mEqualizer);

	mRunner = (mRunner + 1) % (8 - (2*mEqualizer));
	if (mRunner == 0)
		mEqualizer = (mEqualizer + 1) % 4;
}