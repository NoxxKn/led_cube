#include <string>

#include "Application.h"
#include "GL/glut.h"
#include "../XEvent/GUICreatorEvent/CreateMainViewEvent.h"

using namespace std;
using namespace NX;

Application * Application::mInstance = NULL;

Application * Application::getInstance() {
	if (mInstance == NULL)
		mInstance = new Application();
	return mInstance;
}

Application::Application()
: mWindow(NX_APPLICATION_WIDTH, NX_APPLICATION_HEIGHT,
NX_APPLICATION_ORTHO_L, NX_APPLICATION_ORTHO_R,
NX_APPLICATION_ORTHO_T, NX_APPLICATION_ORTHO_B,
NX_APPLICATION_ORTHO_N, NX_APPLICATION_ORTHO_F,
NX_APPLICATION_POS_X, NX_APPLICATION_POS_Y,
NX_APPLICATION_CLEAR_R, NX_APPLICATION_CLEAR_G,
NX_APPLICATION_CLEAR_B, NX_APPLICATION_CLEAR_A,
"Cube Studio!") {
	mEventManager = EventManager::getInstance();
	mTaskManager = TaskManager::getInstance();
	mCommandManager = CommandManager::getInstance();
}

Application::~Application() {
	delete mEventManager;
	delete mTaskManager;
	delete mCommandManager;

	mThread.join();

	if (mInstance != NULL)
		mInstance = NULL;
}

MainWindow * Application::window() {
	return &mWindow;
}

EventManager * Application::eventManager() {
	return mEventManager;
}

TaskManager * Application::taskManager() {
	return mTaskManager;
}

CommandManager * Application::commandManager() {
	return mCommandManager;
}

void Application::init() {
	regCommands();
	mEventManager->add(new CreateMainViewEvent());
	mThread = thread(cmdThread);
}

void Application::mainloop(int elapsedTime) {
	lockMutex();

	mEventManager->trigger();
	mTaskManager->trigger(elapsedTime);

	unlockMutex();
}

void Application::reset() {
	// reset View
	mWindow.reset();
	// free memory
	delete mEventManager;
	delete mTaskManager;
	// create new Manager
	mEventManager = EventManager::getInstance();
	mTaskManager = TaskManager::getInstance();
}

void Application::lockMutex() {
	mMutex.lock();
}

void Application::unlockMutex() {
	mMutex.unlock();
}

void Application::regCommands() {

}

list<string> NX::explode(const string& str, const char& ch) {
	string next;
	list<string> result;

	// For each character in the string
	for (string::const_iterator it = str.begin(); it != str.end(); it++) {
		// If we've hit the terminal character
		if (*it == ch) {
			// If we have some characters accumulated
			if (!next.empty()) {
				// Add them to the result vector
				result.push_back(next);
				next.clear();
			}
		}
		else {
			// Accumulate the next character into the sequence
			next += *it;
		}
	}
	if (!next.empty())
		result.push_back(next);
	return result;
}

void NX::cmdThread() {
	bool go = true;
	list<string> l;
	string s;
	string cmd;

	while (go) {
		cout << "OSMC cmd << ";
		getline(cin, s);
		l = explode(s, ' ');
		if (s.size() > 0 && l.size() > 0) {
			cmd = *l.begin();

			if (cmd.compare("end") == 0)
				go = false;
			else {
				l.erase(l.begin());
				Application::getInstance()->lockMutex();
				CommandManager::getInstance()->setValues(l);
				CommandManager::getInstance()->cmd(cmd)->exec();
				Application::getInstance()->unlockMutex();
			}
		}
	}
}
