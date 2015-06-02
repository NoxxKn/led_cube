#include <iostream>
#include "LOLEffect.h"

using namespace std;
using namespace NX;

/*
. . . . . . . . 7
. . . . . . . . 6
. . . . . . . . 5
. . . . . . . . 4	
o . . o o . o . 3   3,0 3,3 3,4 3,6
o . o . . o o . 2	2,0 2,2 2,5 2,6
o . o . . o o . 1	1,0 1,2 1,5 1,6
o o . o o . o o 0   0,0 0,1 0,3 0,4 0,6 0,7
0 1 2 3 4 5 6 7

*/

uint8_t LOLEffect::mX1[18] = { 0., 0., 0., 0.,
1., 2., 2., 3., 3., 5., 5., 4., 4., 6., 6.,
6., 6., 7. };
uint8_t LOLEffect::mX2[18] = { 7., 7., 7., 7.,
6., 5., 5., 4., 4., 2., 2., 3., 3., 1., 1.,
1., 1., 0. };
uint8_t LOLEffect::mY1[18] = { 0., 0., 0., 0,
0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.,
0., 0., 0. };
uint8_t LOLEffect::mY2[18] = { 7., 7., 7., 7,
7., 7., 7., 7., 7., 7., 7., 7., 7., 7., 7.,
7., 7., 7. };
uint8_t LOLEffect::mZ[18] = { 2., 3., 4., 5.,
2., 3., 4., 5., 2., 3., 4., 5., 2., 3., 4.,
5., 2., 2. };

void LOLEffect::run() {
	clearAll();
	for (int i = 0; i < 18; ++i) {
		uint8_t iX1, iX2, iZ, iY1, iY2;
		//iX1 = mX1[i];
		iX2 = mX2[i];
		iY1 = mY1[i] + mYRunner;
		//iY2 = mY2[i];
		iZ = mZ[i];
		//setLed(iX1, iY2, iZ);
		setLed(iY1, iX2, iZ);
		// setLed(iX2, iY1, iZ);
	}
	mYRunner = (mYRunner + 1) % 8;
	
}