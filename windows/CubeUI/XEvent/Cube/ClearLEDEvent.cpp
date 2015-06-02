#include "ClearLEDEvent.h"
#include "../../Application/Application.h"

using namespace std;
using namespace NX;

void ClearLEDEvent::trigger() {
	Application * app = Application::getInstance();
	mutex * m = app->cubesMutex();
	m->lock();
	vector<Cube*> * cubes = app->cubes();
	size_t cubesSize = cubes->size();
	for (size_t i = 0; i < cubesSize; ++i) {
		Cube * cube = cubes->at(i);
		if (cube->comNum() == mCOMNumber) {
			cube->clearAll();
			cube->writeControl();
			break;
		}
	}
	m->unlock();
}