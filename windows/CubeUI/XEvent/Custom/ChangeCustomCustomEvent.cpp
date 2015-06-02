#include "ChangeCustomCustomEvent.h"
#include "../../Application/Application.h"
#include "../../Effect/CustomEffect.h"

using namespace std;
using namespace NX;

void ChangeCustomCustomEvent::trigger() {
	Application * app = Application::getInstance();

	// load Custom Name
	size_t newVal = mVal;

	// lock mutex
	mutex * m = app->cubesMutex();
	m->lock();

	// execute
	app->customNum(newVal);

	// unlock mutex
	m->unlock();
}