#include <sstream>
#include "ClearLayerCustomCommand.h"
#include "../../Application/Application.h"
#include "../../Effect/CustomEffect.h"
#include"../../XEvent/Custom/ClearLayerCustomEvent.h"

using namespace std;
using namespace NX;

void ClearLayerCustomCommand::exec() {
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

	// load custom Name and layer
	string customName = "";
	size_t layer = 0;
	ss << *itr;
	ss >> customName;
	ss = stringstream();
	ss << *(++itr);
	ss >> layer;

	app->eventManager()->add(new ClearLayerCustomEvent(customName, layer));
}