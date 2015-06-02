#include <sstream>
#include "ClearLedCustomCommand.h"
#include "../../Application/Application.h"
#include "../../Effect/CustomEffect.h"
#include "../../XEvent/Custom/ClearLedCustomEvent.h"

using namespace std;
using namespace NX;

void ClearLedCustomCommand::exec() {
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

	// load custom Name layer x y z
	string customName = "";
	size_t layer = 0, x = 0, y = 0, z = 0;
	ss << *itr;
	ss >> customName;
	ss = stringstream();
	ss << *(++itr);
	ss >> layer;
	ss = stringstream();
	ss << *(++itr);
	ss >> x;
	ss = stringstream();
	ss << *(++itr);
	ss >> y;
	ss = stringstream();
	ss << *(++itr);
	ss >> z;

	app->eventManager()->add(new ClearLedCustomEvent(customName, layer, x, y, z));
}