#include <sstream>
#include <algorithm>
#include "RemoveEffectCommand.h"
#include "../../Application/Application.h"
#include "../../XEvent/Effect/RemoveEffectEvent.h"

using namespace std;
using namespace NX;

void RemoveEffectCommand::exec() {
	bool hasFound = false;
	Application * app = Application::getInstance();
	CommandManager * cman = app->commandManager();
	string effectName;
	list<string> values = cman->getLoadValues();
	list<string>::iterator itr;

	itr = values.begin();

	stringstream ss;

	ss << *itr;
	ss >> effectName;

	app->eventManager()->add(new RemoveEffectEvent(effectName));
}