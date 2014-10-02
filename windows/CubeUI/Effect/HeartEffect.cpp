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
. . o . . o . . 2   2,2 2,5
. . . o o . . . 1	3,1 4,1
. . . . . . . . 0
0 1 2 3 4 5 6 7


R_y(\alpha) = \begin{pmatrix}
\cos \alpha  & 0 & \sin \alpha \\
0         & 1 &  0          \\
-\sin \alpha & 0 & \cos \alpha
\end{pmatrix}
x	cos  0 sin
y	0    0 0
z	-sin 0 cos
*/

double HeartEffect::mX[14] = { 2. - 4.5, 1. - 4.5,
0. - 4.5, 1. - 4.5, 2. - 4.5, 3. - 4.5,
5. - 4.5, 3. - 4.5, 7. - 4.5, 6. - 4.5,
2. - 4.5, 4. - 4.5, 4. - 4.5, 6. - 4.5 };
double HeartEffect::mY[14] = { 6., 5.,
4., 3., 2., 1.,
6., 5., 4., 3.,
2. , 1., 5., 5.};
double HeartEffect::mZ[14] = { 4.5 - 4.5, 4.5 - 4.5, 4.5 - 4.5, 4.5 - 4.5, 4.5 - 4.5,
4.5 - 4.5, 4.5 - 4.5, 4.5 - 4.5, 4.5 - 4.5, 4.5 - 4.5,
4.5 - 4.5, 4.5 - 4.5, 4.5 - 4.5, 4.5 - 4.5 };

void HeartEffect::run() {
	clearAll();
	for (int i = 0; i < 14; ++i) {
		double x, y, z;

		x = mX[i];
		z = mZ[i];
		y = mY[i];

		double bufx, bufy, bufz;
		/*
		x	cos  -sin 0
		y	sin  cos  0
		z	0    0    0
		*/
		bufx = x * cos(mRotation) + z * sin(mRotation);
		bufy = y;
		bufz = x * (-sin(mRotation)) + z * cos(mRotation);
		//bufx = x;
		//bufy = y;
		//bufz = z;

		int iX = round(bufx+4.5);
		int iY = round(bufy);
		int iZ = round(bufz+4.5);
		setLed(iX, iZ, iY);
	}
	mRotation += 0.01;
}