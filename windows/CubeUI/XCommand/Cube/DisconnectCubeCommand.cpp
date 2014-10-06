#include <sstream>
#include "DisconnectCubeCommand.h"
#include "../../Application/Application.h"
#include "../../XEvent/Cube/DisconnectCubeEvent.h"

using namespace std;
using namespace NX;

void DisconnectCubeCommand::exec() {
	Application * app = Application::getInstance();
	CommandManager * cman = app->commandManager();
	int mCOMNumber;
	list<string> values = cman->getLoadValues();
	list<string>::iterator itr;

	itr = values.begin();

	stringstream ss;

	ss << *itr;
	ss >> mCOMNumber;

	app->eventManager()->add(new DisconnectCubeEvent(mCOMNumber));
}