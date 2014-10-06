#include <sstream>
#include "SetPlaneCustomCommand.h"
#include "../../Application/Application.h"
#include "../../Effect/CustomEffect.h"
#include "../../XEvent/Custom/SetPlaneCustomEvent.h"

using namespace std;
using namespace NX;

void SetPlaneCustomCommand::exec() {
	Application * app = Application::getInstance();
	// loadValues
	CommandManager * cman = app->commandManager();
	list<string> values = cman->getLoadValues();
	list<string>::iterator itr;
	itr = values.begin();
	stringstream ss;

	// check values size
	if (values.size() != 4)
		return;

	// load custom Name layer x y z
	string customName = "";
	size_t layer = 0, val = 0;
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
	ss >> val;

	app->eventManager()->add(new SetPlaneCustomEvent(customName, layer, val, row));
}