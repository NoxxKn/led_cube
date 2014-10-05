#include <sstream>
#include "ClearLEDCommand.h"
#include "../../Application/Application.h"

using namespace std;
using namespace NX;

void ClearLEDCommand::exec() {
	Application * app = Application::getInstance();
	CommandManager * cman = app->commandManager();
	int mCOMNumber;
	list<string> values = cman->getLoadValues();
	list<string>::iterator itr;

	itr = values.begin();

	stringstream ss;

	ss << *itr;
	ss >> mCOMNumber;

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