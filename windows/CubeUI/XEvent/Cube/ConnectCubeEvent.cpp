#include "ConnectCubeEvent.h"
#include "../../Application/Application.h"

using namespace std;
using namespace NX;

void ConnectCubeEvent::trigger() {
	Application * app = Application::getInstance();
	Cube * cube = new Cube();

	bool success = cube->cubeConnect(mCOMNumber, mBaudRate, mParityBit, mByteSize, mStopBits);

	if (success) {
		mutex * m = app->cubesMutex();
		m->lock();
		app->addCube(cube);
		m->unlock();
		cout << "COM Success! " << endl;
		cout << "Connected to COM: " << mCOMNumber << endl;
	}
	else {
		cout << "COM No Success" << endl;
		delete cube;
	}
}