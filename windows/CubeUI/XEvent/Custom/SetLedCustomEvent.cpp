#include "SetLedCustomEvent.h"
#include "../../Application/Application.h"
#include "../../Effect/CustomEffect.h"

using namespace std;
using namespace NX;

void SetLedCustomEvent::trigger() {
	Application * app = Application::getInstance();

	// load custom Name layer x y z
	string customName = mCustomName;
	size_t layer = mLayer, x = mX, y = mY, z = mZ;

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
		custom->setLed(layer, x, y, z);
	}

	// unlock mutex
	m->unlock();
}