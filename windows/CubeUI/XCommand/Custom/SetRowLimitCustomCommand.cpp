#include <sstream>
#include "SetRowLimitCustomCommand.h"
#include "../../Application/Application.h"
#include "../../Effect/CustomEffect.h"

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

	// lock mutex
	mutex * m = app->cubesMutex();
	m->lock();

	// find custom Command
	bool found = false;
	list<IEffect*> * effects = app->effects();
	list<IEffect*>::iterator etr;
	CustomEffect * custom = NULL;
	for (etr = effects->begin(); etr != effects->end(); ++etr) {
		IEffect * ef = *etr;
		if (ef->type() == ET_CUSTOM) {
			CustomEffect * ce = (CustomEffect*)ef;
			if (customName == ce->name())
				custom = ce;
		}
	}

	// execute
	if (custom) {
		if (row == 'x')
			custom->setRowX(layer, val1, val2, begin, end);
		else if (row == 'y')
			custom->setRowY(layer, val1, val2, begin, end);
		else if (row == 'z')
			custom->setRowZ(layer, val1, val2, begin, end);
	}

	// unlock mutex
	m->unlock();
}