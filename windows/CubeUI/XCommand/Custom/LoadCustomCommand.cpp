#include <sstream>
#include <fstream>
#include "LoadCustomCommand.h"
#include "../../Application/Application.h"
#include "../../Effect/CustomEffect.h"
#include "../../XEvent/Custom/LoadCustomEvent.h"

using namespace std;
using namespace NX;

void LoadCustomCommand::exec() {
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
	ss = stringstream();
	
	app->eventManager()->add(new LoadCustomEvent(customName, fileName));
}