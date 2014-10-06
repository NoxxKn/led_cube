#include "DisconnectCubeEvent.h"
#include "../../Application/Application.h"

using namespace std;
using namespace NX;

void DisconnectCubeEvent::trigger() {
	Application * app = Application::getInstance();
	mutex * m = app->cubesMutex();
	m->lock();
	app->removeCube(mCOMNumber);
	m->unlock();
}