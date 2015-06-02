#include <sstream>
#include "ShowCubesCommand.h"
#include "../../Application/Application.h"
#include "../../XEvent/Cube/ShowCubesEvent.h"

using namespace std;
using namespace NX;

void ShowCubesCommand::exec() {
	Application * app = Application::getInstance();

	app->eventManager()->add(new ShowCubesEvent());
}