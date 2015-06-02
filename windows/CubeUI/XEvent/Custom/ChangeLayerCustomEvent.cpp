#include "ChangeLayerCustomEvent.h"
#include "../../Application/Application.h"
#include "../../Effect/CustomEffect.h"

using namespace std;
using namespace NX;

void ChangeLayerCustomEvent::trigger() {
	Application * app = Application::getInstance();

	// load Custom Name
	size_t newVal = mLayer;

	// lock mutex
	mutex * m = app->cubesMutex();
	m->lock();

	// execute
	app->layerNum(newVal);

	// unlock mutex
	m->unlock();
}