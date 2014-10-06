#include "ChangeModeEvent.h"
#include "../../Application/Application.h"

using namespace std;
using namespace NX;

void ChangeModeEvent::trigger() {
	Application * app = Application::getInstance();

	// load Custom Name
	string mode = mMode;

	// lock mutex
	mutex * m = app->cubesMutex();
	m->lock();

	// execute
	if (mode == "effects")
		app->playMode(PM_EFFECTS);
	else if (mode == "custom")
		app->playMode(PM_CUSTOM);
	else
		cout << "Unknown Mode!" << endl;

	// unlock mutex
	m->unlock();
}