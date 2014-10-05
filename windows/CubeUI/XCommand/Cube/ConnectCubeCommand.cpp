#include <sstream>
#include "ConnectCubeCommand.h"
#include "../../Application/Application.h"

using namespace std;
using namespace NX;

void ConnectCubeCommand::exec() {
	Application * app = Application::getInstance();
	CommandManager * cman = app->commandManager();

	list<string> values = cman->getLoadValues();
	list<string>::iterator itr;

	itr = values.begin();

	stringstream ss;

	ss << *itr;
	ss >> mCOMNumber;

	Cube * cube = new Cube();
	bool success = cube->cubeConnect(mCOMNumber);

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