#include <sstream>
#include "ShowEffectsCommand.h"
#include "../../Application/Application.h"
#include "../../XEvent/Effect/ShowEffectsEvent.h"

using namespace std;
using namespace NX;

void ShowEffectsCommand::exec() {
	Application * app = Application::getInstance();

	app->eventManager()->add(new ShowEffectsEvent());
}