#include <sstream>
#include "ConnectCubeCommand.h"
#include "../../Application/Application.h"
#include "../../XEvent/Cube/ConnectCubeEvent.h"

using namespace std;
using namespace NX;

void ConnectCubeCommand::exec() {
	Application * app = Application::getInstance();
	CommandManager * cman = app->commandManager();

	list<string> values = cman->getLoadValues();
	list<string>::iterator itr;

	itr = values.begin();

	stringstream ss;
	ss << *itr;
	ss >> mCOMNumber;

	if (values.size() > 1) {
		ss = stringstream();
		ss << *(++itr);
		ss >> mBaudRate;
	}
	if (values.size() > 2) {
		ss = stringstream();
		ss << *(++itr);
		ss >> mByteSize;
	}
	if (values.size() > 3) {
		ss = stringstream();
		ss << *(++itr);
		ss >> mParityBit;
	}
	if (values.size() > 4) {
		ss = stringstream();
		ss << *(++itr);
		ss >> mStopBits;
	}

	IEvent * e = NULL;
	if (values.size() == 1)
		e = new ConnectCubeEvent(mCOMNumber);
	else if (values.size() == 2)
		e = new ConnectCubeEvent(mCOMNumber, mBaudRate);
	else if (values.size() == 3)
		e = new ConnectCubeEvent(mCOMNumber, mBaudRate, mParityBit);
	else if (values.size() == 4)
		e = new ConnectCubeEvent(mCOMNumber, mBaudRate, mParityBit, mByteSize);
	else if (values.size() == 5)
		e = new ConnectCubeEvent(mCOMNumber, mBaudRate, mParityBit, mByteSize, mStopBits);
	
	if (e)
		app->eventManager()->add(e);
}