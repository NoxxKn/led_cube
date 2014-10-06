#include <sstream>
#include <algorithm>
#include "AddEffectCommand.h"
#include "../../Application/Application.h"
#include "../../Effect/HeartEffect.h"
#include "../../Effect/LOLEffect.h"
#include "../../Effect/MatrixEffect.h"
#include "../../Effect/PlaneEffect.h"
#include "../../Effect/RandomEffect.h"
#include "../../Effect/SinEffect.h"
#include "../../Effect/RainEffect.h"
#include "../../Effect/CustomEffect.h"
#include "../../XEvent/Effect/AddEffectEvent.h"

using namespace std;
using namespace NX;

void AddEffectCommand::exec() {
	Application * app = Application::getInstance();
	CommandManager * cman = app->commandManager();
	string effectName;
	string customName = "";
	list<string> values = cman->getLoadValues();
	list<string>::iterator itr;

	itr = values.begin();

	stringstream ss;

	if (values.size() == 0)
		return;

	ss << *itr;
	ss >> effectName;

	ss = stringstream();

	if (values.size() == 2) {
		ss << *(++itr);
		ss >> customName;
	}

	app->eventManager()->add(new AddEffectEvent(effectName, customName));
}