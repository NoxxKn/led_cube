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
	mGoon.store(true);
	mEventManager = EventManager::getInstance();
	mTaskManager = TaskManager::getInstance();
	mCommandManager = CommandManager::getInstance();
}

Application::~Application() {
	mGoon.store(false);

	mWriterThread.join();
	mCommandThread.join();

	delete mEventManager;
	delete mTaskManager;
	delete mCommandManager;

	list<IEffect*>::iterator etr;
	for (etr = mEffects.begin(); etr != mEffects.end(); ++etr)
		delete *etr;
	mEffects.clear();

	vector<Cube*>::iterator ctr;
	for (ctr = mCubes.begin(); ctr != mCubes.end(); ++ctr)
		delete *ctr;
	mCubes.clear();

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

void Application::addCube(Cube * cube) {
	mCubes.push_back(cube);
}

Cube * Application::cube(size_t pos) {
	return mCubes[pos];
}

size_t Application::cubesSize() const {
	return mCubes.size();
}

void Application::addEffect(IEffect * ef) {
	mCubesMutex.lock();
	mEffects.push_back(ef);
	mCubesMutex.unlock();
}

list<IEffect*> Application::copyEffects() {
	mCubesMutex.lock();
	list<IEffect*> copyList = mEffects;
	mCubesMutex.unlock();
	return copyList;
}

list<IEffect*> * Application::effects() {
	return &mEffects;
}

bool Application::goon() const {
	return mGoon.load();
}

void Application::kill() {
	mGoon.store(false);
	mCubesMutex.lock();
	vector<Cube*>::iterator ctr;
	for (ctr = mCubes.begin(); ctr != mCubes.end(); ++ctr)
		delete *ctr;
	mCubes.clear();
	mCubesMutex.unlock();
}

mutex * Application::taskMutex() {
	return &mTaskMutex;
}

mutex * Application::cubesMutex() {
	return &mCubesMutex;
}

void Application::init() {
	regCommands();
	mEventManager->add(new CreateMainViewEvent());
	mCommandThread = thread(cmdThread);
	mWriterThread = thread(effThread);
}

void Application::mainloop(int elapsedTime) {
	mTaskMutex.lock();

	mEventManager->trigger();
	mTaskManager->trigger(elapsedTime);

	mTaskMutex.unlock();
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
	Application * app = Application::getInstance();
	bool go = app->goon();
	list<string> l;
	string s;
	string cmd;

	while (go) {
		cout << "OSMC cmd << ";
		getline(cin, s);
		l = explode(s, ' ');
		if (s.size() > 0 && l.size() > 0) {
			cmd = *l.begin();

			if (cmd.compare("end") == 0) {
				go = false;
				app->kill();
			}
			else {
				l.erase(l.begin());
				app->taskMutex()->lock();
				CommandManager::getInstance()->setValues(l);
				CommandManager::getInstance()->cmd(cmd)->exec();
				app->taskMutex()->unlock();
			}
		}
		go = app->goon();
	}
}

void NX::effThread() {
	Application * app = Application::getInstance();
	mutex * mtx = app->cubesMutex();
	bool go = app->goon();

	while (go) {
		mtx->lock();

		if (app->cubesSize() > 0) {
			Cube * cub = app->cube(0);

			list<IEffect*> * effects = app->effects();
			list<IEffect*>::const_iterator itr;
			for (itr = effects->begin(); itr != effects->end(); ++itr) {
				IEffect * effect = *itr;
				effect->run();
				CubeControl con = effect->control();
				cub->setControl(con);
				cub->writeControl();
			}
		}

		mtx->unlock();

		go = app->goon();
	}
}