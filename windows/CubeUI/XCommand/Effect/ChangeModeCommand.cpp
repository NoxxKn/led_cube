#include <sstream>
#include "ChangeModeCommand.h"
#include "../../Application/Application.h"

using namespace std;
using namespace NX;

void ChangeModeCommand::exec() {
	Application * app = Application::getInstance();
	// loadValues
	CommandManager * cman = app->commandManager();
	list<string> values = cman->getLoadValues();
	list<string>::iterator itr;
	itr = values.begin();
	stringstream ss;

	// check values size
	if (values.size() != 1)
		return;

	// load Custom Name
	string mode = "";
	ss << *itr;
	ss >> mode;

	// lock mutex
	mutex * m = app->cubesMutex();
	m->lock();

	// execute
	if (mode == "effects")
		app->playMode(PM_EFFECTS);
	else if (mode == "custom")
		app->playMode(PM_CUSTOM);
	else
		cout << "Unknown Mode!" << endl;

	// unlock mutex
	m->unlock();
}