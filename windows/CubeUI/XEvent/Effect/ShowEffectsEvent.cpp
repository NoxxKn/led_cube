#include <string>
#include "ShowEffectsEvent.h"
#include "../../Application/Application.h"

using namespace std;
using namespace NX;

void ShowEffectsEvent::trigger() {
	Application * app = Application::getInstance();

	mutex * m = app->cubesMutex();
	m->lock();
	list<IEffect*> * effects = app->effects();
	list<IEffect*>::iterator etr;
	size_t counter = 0;
	for (etr = effects->begin(); etr != effects->end(); ++etr) {
		IEffect * ef = *etr;
		cout << "Effect[" << counter++ << "]: " << ef->name() << " Layer: " << ef->times() << endl;
	}
	m->unlock();

}