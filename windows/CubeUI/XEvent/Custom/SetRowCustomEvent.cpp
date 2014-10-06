#include "SetRowCustomEvent.h"
#include "../../Application/Application.h"
#include "../../Effect/CustomEffect.h"

using namespace std;
using namespace NX;

void SetRowCustomEvent::trigger() {
	Application * app = Application::getInstance();

	// load custom Name
	string customName = mCustomName;
	size_t layer = mLayer, val1 = mVal1, val2 = mVal2;
	char row = mRow;

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
			custom->setRowX(layer, val1, val2);
		else if (row == 'y')
			custom->setRowY(layer, val1, val2);
		else if (row == 'z')
			custom->setRowZ(layer, val1, val2);
	}

	// unlock mutex
	m->unlock();
}