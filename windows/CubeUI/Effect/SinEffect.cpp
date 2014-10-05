#include <iostream>
#include "SinEffect.h"

using namespace std;
using namespace NX;

void SinEffect::run() {
	double y[] = { 0, 1, 2, 1, 0, -1, -2, -1 };
	clearAll();
	for (int i = 0; i < 8; ++i) {
		size_t pos = (i + mRunner) % 8;
		double val = y[pos] + 4;
		// setRowY(i, round(val));
		setRowX(i, round(val));
	}
	mRunner = (mRunner + 1) % 8;
}