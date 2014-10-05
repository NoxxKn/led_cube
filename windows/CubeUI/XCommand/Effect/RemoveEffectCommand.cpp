#include <sstream>
#include <algorithm>
#include "RemoveEffectCommand.h"
#include "../../Application/Application.h"

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

	mutex * m = app->cubesMutex();
	m->lock();
	list<IEffect*> * effects = app->effects();
	list<IEffect*>::iterator etr;
	for (etr = effects->begin(); etr != effects->end(); ++etr) {
		IEffect * ef = *etr;
		string curName = ef->name();
		transform(curName.begin(), curName.end(), curName.begin(), tolower);
		transform(effectName.begin(), effectName.end(), effectName.begin(), tolower);
		if (effectName == curName) {
			effects->remove(ef);
			cout << "Effect was removed: " << effectName << endl;
			hasFound = true;
			delete ef;
			break;
		}
	}
	m->unlock();

	if (!hasFound) {
		cout << "There is no effect named: " << effectName << endl;
	}
}