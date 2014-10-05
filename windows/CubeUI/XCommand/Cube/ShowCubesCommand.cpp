#include <sstream>
#include "ShowCubesCommand.h"
#include "../../Application/Application.h"

using namespace std;
using namespace NX;

void ShowCubesCommand::exec() {
	Application * app = Application::getInstance();
	CommandManager * cman = app->commandManager();

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