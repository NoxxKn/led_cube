#include <sstream>
#include "ChangeModeCommand.h"
#include "../../Application/Application.h"
#include "../../XEvent/Effect/ChangeModeEvent.h"

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

	app->eventManager()->add(new ChangeModeEvent(mode));
}