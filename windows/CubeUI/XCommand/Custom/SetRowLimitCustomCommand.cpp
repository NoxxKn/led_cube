#include <sstream>
#include "SetRowLimitCustomCommand.h"
#include "../../Application/Application.h"
#include "../../Effect/CustomEffect.h"
#include "../../XEvent/Custom/SetRowLimitCustomEvent.h"

using namespace std;
using namespace NX;

void SetRowLimitCustomCommand::exec() {
	Application * app = Application::getInstance();
	// loadValues
	CommandManager * cman = app->commandManager();
	list<string> values = cman->getLoadValues();
	list<string>::iterator itr;
	itr = values.begin();
	stringstream ss;

	// check values size
	if (values.size() != 7)
		return;

	// load custom Name
	string customName = "";
	size_t layer = 0, val1 = 0, val2 = 0, begin = 0, end = 0;
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
	ss = stringstream();
	ss << *(++itr);
	ss >> begin;
	ss = stringstream();
	ss << *(++itr);
	ss >> end;

	app->eventManager()->add(new SetRowLimitCustomEvent(customName, layer, val1, val2, row, begin, end));
}