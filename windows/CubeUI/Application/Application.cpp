#include <string>
#include <algorithm>
#include "Application.h"
#include "GL/glut.h"
#include "../XEvent/GUICreatorEvent/CreateMainViewEvent.h"
#include "../XCommand/Cube/ConnectCubeCommand.h"
#include "../XCommand/Cube/DisconnectCubeCommand.h"
#include "../XCommand/Cube/ShowCubesCommand.h"
#include "../XCommand/Cube/ClearLEDCommand.h"
#include "../XCommand/Effect/AddEffectCommand.h"
#include "../XCommand/Effect/RemoveEffectCommand.h"
#include "../XCommand/Effect/ShowEffectsCommand.h"
#include "../XCommand/Effect/ChangeModeCommand.h"
#include "../XCommand/Custom/AddLayerCustomCommand.h"
#include "../XCommand/Custom/ChangeCustomCustomCommand.h"
#include "../XCommand/Custom/ChangeLayerCustomCommand.h"
#include "../XCommand/Custom/ClearLayerCustomCommand.h"
#include "../XCommand/Custom/ClearLedCustomCommand.h"
#include "../XCommand/Custom/ClearRowCustomCommand.h"
#include "../XCommand/Custom/RemoveLayerCustomCommand.h"
#include "../XCommand/Custom/SetLedCustomCommand.h"
#include "../XCommand/Custom/SetPlaneCustomCommand.h"
#include "../XCommand/Custom/SetRowCustomCommand.h"
#include "../XCommand/Custom/SetRowLimitCustomCommand.h"
#include "../Effect/CustomEffect.h"

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
	mPlayMode = PM_EFFECTS;
	mCustomNum = 0;
	mLayerNum = 0;
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

void Application::removeCube(int comNum) {
	size_t sizeCubes = mCubes.size();

	for (size_t i = 0; i < sizeCubes; ++i) {
		Cube * cube = mCubes[i];
		if (cube->comNum() == comNum) {
			vector<Cube*>::iterator itr = mCubes.begin();
			advance(itr, i);
			delete cube;
			mCubes.erase(itr);
			cout << "Cube COM Num: " << comNum << " disconnected!" << endl;
			return;
		}
	}

	cout << "No Cube on COM Num: " << comNum << " found!" << endl;
}

vector<Cube*> * Application::cubes() {
	return &mCubes;
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

PlayMode Application::playMode() const {
	return mPlayMode;
}

void Application::playMode(PlayMode playMode) {
	mPlayMode = playMode;
}

size_t Application::customNum() const {
	return mCustomNum;
}

void Application::customNum(size_t num) {
	mCustomNum = num;
}

size_t Application::layerNum() const {
	return mLayerNum;
}

void Application::layerNum(size_t num) {
	mLayerNum = num;
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
	mCommandManager->reg("connectCube", new ConnectCubeCommand());
	mCommandManager->reg("disconnectCube", new DisconnectCubeCommand());
	mCommandManager->reg("showCubes", new ShowCubesCommand());
	mCommandManager->reg("addEffect", new AddEffectCommand());
	mCommandManager->reg("removeEffect", new RemoveEffectCommand());
	mCommandManager->reg("showEffects", new ShowEffectsCommand());
	mCommandManager->reg("clearLED", new ClearLEDCommand());
	mCommandManager->reg("changeMode", new ChangeModeCommand());
	mCommandManager->reg("addLayer", new AddLayerCustomCommand());
	mCommandManager->reg("changeCustom", new ChangeCustomCustomCommand());
	mCommandManager->reg("changeLayer", new ChangeLayerCustomCommand());
	mCommandManager->reg("clearLayer", new ClearLayerCustomCommand());
	mCommandManager->reg("clearLed", new ClearLedCustomCommand());
	mCommandManager->reg("clearRow", new ClearRowCustomCommand());
	mCommandManager->reg("removeLayer", new RemoveLayerCustomCommand());
	mCommandManager->reg("setLed", new SetLedCustomCommand());
	mCommandManager->reg("setPlane", new SetPlaneCustomCommand());
	mCommandManager->reg("setRow", new SetRowCustomCommand());
	mCommandManager->reg("setRowLimit", new SetRowLimitCustomCommand());
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
				CommandManager * cman = CommandManager::getInstance();
				if (cman->isCmd(cmd)) {
					cman->setValues(l);
					cman->cmd(cmd)->exec();
				}
				else {
					cout << "Unknown Command" << endl;
				}
				app->taskMutex()->unlock();
			}
		}
		go = app->goon();
	}
}

void NX::effThread() {
	unsigned int number = 0;
	unsigned int counter = 0;
	size_t posEffects = 0;
	size_t times = 1;
	Application * app = Application::getInstance();
	mutex * mtx = app->cubesMutex();
	bool go = app->goon();

	while (go) {
		mtx->lock();

		if (app->cubesSize() > 0 && app->playMode() == PM_EFFECTS) {
			Cube * cub = app->cube(0);

			list<IEffect*> * effects = app->effects();
			list<IEffect*>::const_iterator itr = effects->begin();
			size_t pos = posEffects;
			number = effects->size();
			if (pos >= number) {
				pos = 0;
				posEffects = 0;
			}
			if (pos < number) {
				advance(itr, pos);
				IEffect * effect = *itr;
				if (effect->times() > 0) {
					effect->run();
					CubeControl con = effect->control();
					cub->setControl(con);
					cub->writeControl();

					times = effect->times();
					counter = (counter + 1) % times;
					if (counter == 0)
						posEffects++;
				} else
					posEffects++;
			}
		} else if(app->cubesSize() > 0 && app->playMode() == PM_CUSTOM) {
			Cube * cube = app->cube(0);

			list<IEffect*> * effects = app->effects();
			list<IEffect*>::const_iterator itr = effects->begin();
			size_t cusNum = app->customNum();
			size_t layNum = app->layerNum();
			IEffect * ef = NULL;
			IEffect * runner = NULL;
			size_t ctCount = 0;

			// search for effect
			for (itr = effects->begin(); itr != effects->end(); ++itr) {
				runner = *itr;
				if (runner->type() == ET_CUSTOM) {
					if (ctCount == cusNum) {
						ef = runner;
						break;
					} else {
						ctCount++;
					}
				}
			}

			// now ef is still null or there is the right effect in ef
			if (ef != NULL) {
				CustomEffect * cus = (CustomEffect*)ef;
				if (cus->sizeLayers() > layNum) {
					CubeControl con = cus->control(layNum);
					cube->setControl(con);
					cube->writeControl();
				}
			}
		}

		mtx->unlock();
		
		go = app->goon();
	}
}