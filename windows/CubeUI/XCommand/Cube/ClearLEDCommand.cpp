#include <sstream>
#include "ClearLEDCommand.h"
#include "../../Application/Application.h"
#include "../../XEvent/Cube/ClearLEDEvent.h"

using namespace std;
using namespace NX;

void ClearLEDCommand::exec() {
	Application * app = Application::getInstance();
	CommandManager * cman = app->commandManager();
	int mCOMNumber;
	list<string> values = cman->getLoadValues();
	list<string>::iterator itr;

	if (values.size() != 1)
		return;

	itr = values.begin();

	stringstream ss;

	ss << *itr;
	ss >> mCOMNumber;

	app->eventManager()->add(new ClearLEDEvent(mCOMNumber));
}