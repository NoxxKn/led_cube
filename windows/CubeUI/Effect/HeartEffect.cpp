#include <iostream>
#include "HeartEffect.h"

using namespace std;
using namespace NX;

/*
. . . . . . . . 7
. . o . . o . . 6	2,6 5,6
. o . o o . o . 5   1,5 3,5 4,5 6,5
o . . . . . . o 4	0,4 7,4
. o . . . . o . 3	1,3 6,3
. . o . . o . . 2   2,2 5,2
. . . o o . . . 1	3,1 4,1
. . . . . . . . 0
0 1 2 3 4 5 6 7

*/

double HeartEffect::mX[14] = { 2., 1.,
	0., 1., 2., 3.,
	5., 3., 7., 6.,
	5., 4., 4., 6.};
double HeartEffect::mY[14] = { 6., 5.,
	4., 3., 2., 1.,
	6., 5., 4., 3.,
	2. , 1., 5., 5.};
double HeartEffect::mZ[14] = { 
	0., 0., 0., 0., 0.,
	0., 0., 0., 0., 0.,
	0., 0., 0., 0. };

void HeartEffect::run() {
	clearAll();
	for (int i = 0; i < 14; ++i) {
		int x, y, z;

		x = mX[i];
		z = mZ[i];
		y = mY[i];

		z += mRunner;

		setLed(z, x, y);
	}

	mRunner = (mRunner + 1) % 8;
}