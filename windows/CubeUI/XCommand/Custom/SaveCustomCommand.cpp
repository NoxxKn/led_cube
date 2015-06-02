#include <sstream>
#include <fstream>
#include "SaveCustomCommand.h"
#include "../../Application/Application.h"
#include "../../Effect/CustomEffect.h"
#include "../../XEvent/Custom/SaveCustomEvent.h"

using namespace std;
using namespace NX;

void SaveCustomCommand::exec() {
	Application * app = Application::getInstance();
	// loadValues
	CommandManager * cman = app->commandManager();
	list<string> values = cman->getLoadValues();
	list<string>::iterator itr;
	itr = values.begin();
	stringstream ss;

	// check values size
	if (values.size() != 2)
		return;

	// load custom Name
	string customName = "";
	string fileName = "";
	ss << *itr;
	ss >> customName;
	ss = stringstream();
	ss << *(++itr);
	ss >> fileName;

	app->eventManager()->add(new SaveCustomEvent(fileName, customName));
}