#include "AddLayerCustomEvent.h"
#include "../../Application/Application.h"
#include "../../Effect/CustomEffect.h"

using namespace std;
using namespace NX;

void AddLayerCustomEvent::trigger() {
	Application * app = Application::getInstance();

	// load Custom Name
	string customName = mCustomName;

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
		custom->addLayer();
	}

	// unlock mutex
	m->unlock();
}