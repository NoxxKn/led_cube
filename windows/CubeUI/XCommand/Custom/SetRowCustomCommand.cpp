#include <sstream>
#include "SetRowCustomCommand.h"
#include "../../Application/Application.h"
#include "../../Effect/CustomEffect.h"
#include "../../XEvent/Custom/SetRowCustomEvent.h"

using namespace std;
using namespace NX;

void SetRowCustomCommand::exec() {
	Application * app = Application::getInstance();
	// loadValues
	CommandManager * cman = app->commandManager();
	list<string> values = cman->getLoadValues();
	list<string>::iterator itr;
	itr = values.begin();
	stringstream ss;

	// check values size
	if (values.size() != 5)
		return;

	// load custom Name
	string customName = "";
	size_t layer = 0, val1 = 0, val2 = 0;
	char row = '0';
	ss << *itr;
	ss >> customName;
	ss = stringstream();
	ss << *(++itr);
	ss >> layer;
	ss = stringstream();
	ss << *(++itr);
	ss >> row;
	row = tolower(row);
	ss = stringstream();
	ss << *(++itr);
	ss >> val1;
	ss = stringstream();
	ss << *(++itr);
	ss >> val2;

	app->eventManager()->add(new SetRowCustomEvent(customName, layer, val1, val2, row));
}