#include "ShowCubesEvent.h"
#include "../../Application/Application.h"

using namespace std;
using namespace NX;

void ShowCubesEvent::trigger() {
	Application * app = Application::getInstance();

	mutex * m = app->cubesMutex();
	m->lock();
	vector<Cube*> * cubes = app->cubes();
	size_t sizeCubes = cubes->size();
	cout << "Cubes:" << endl;
	size_t counter = 0;
	for (size_t i = 0; i < sizeCubes; ++i) {
		cout << "Cube[" << counter++ << "] Com Number: " << cubes->at(i)->comNum() << endl;
	}
	m->unlock();
}