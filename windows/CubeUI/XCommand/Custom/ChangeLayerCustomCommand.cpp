#include <sstream>
#include "ChangeLayerCustomCommand.h"
#include "../../Application/Application.h"
#include "../../Effect/CustomEffect.h"
#include "../../XEvent/Custom/ChangeLayerCustomEvent.h"

using namespace std;
using namespace NX;

void ChangeLayerCustomCommand::exec() {
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
	size_t newVal = 0;
	ss << *itr;
	ss >> newVal;

	app->eventManager()->add(new ChangeLayerCustomEvent(newVal));
}