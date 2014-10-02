#include <iostream>
#include "RandomEffect.h"

using namespace std;
using namespace NX;

void RandomEffect::run() {
	clearAll();
	for (int i = 0; i < 100; ++i) {
		int x, y, z;

		x = rand() % 8;
		y = rand() % 8;
		z = rand() % 8;
		setLed(x, y, z);
	}
}