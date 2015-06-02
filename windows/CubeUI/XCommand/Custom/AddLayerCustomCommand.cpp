#include <sstream>
#include "AddLayerCustomCommand.h"
#include "../../Application/Application.h"
#include "../../Effect/CustomEffect.h"
#include "../../XEvent/Custom/AddLayerCustomEvent.h"

using namespace std;
using namespace NX;

void AddLayerCustomCommand::exec() {
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
	string customName = "";
	ss << *itr;
	ss >> customName;

	app->eventManager()->add(new AddLayerCustomEvent(customName));
}