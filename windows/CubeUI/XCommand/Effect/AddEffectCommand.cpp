#include <sstream>
#include <algorithm>
#include "AddEffectCommand.h"
#include "../../Application/Application.h"
#include "../../Effect/HeartEffect.h"
#include "../../Effect/LOLEffect.h"
#include "../../Effect/MatrixEffect.h"
#include "../../Effect/PlaneEffect.h"
#include "../../Effect/RandomEffect.h"
#include "../../Effect/SinEffect.h"
#include "../../Effect/RainEffect.h"
#include "../../Effect/CustomEffect.h"

using namespace std;
using namespace NX;

void AddEffectCommand::exec() {
	Application * app = Application::getInstance();
	CommandManager * cman = app->commandManager();
	string effectName;
	string customName = "";
	list<string> values = cman->getLoadValues();
	list<string>::iterator itr;

	itr = values.begin();

	stringstream ss;

	if (values.size() == 0)
		return;

	ss << *itr;
	ss >> effectName;

	ss = stringstream();

	if (values.size() == 2) {
		ss << *(++itr);
		ss >> customName;
	}

	transform(effectName.begin(), effectName.end(), effectName.begin(), tolower);
	transform(customName.begin(), customName.end(), customName.begin(), tolower);

	IEffect * ef = NULL;

	if (effectName == "heart")
		ef = new HeartEffect();
	else if (effectName == "lol")
		ef = new LOLEffect();
	else if (effectName == "matrix")
		ef = new MatrixEffect();
	else if (effectName == "plane")
		ef = new PlaneEffect();
	else if (effectName == "random")
		ef = new RandomEffect();
	else if (effectName == "sin")
		ef = new SinEffect();
	else if (effectName == "rain")
		ef = new RainEffect();
	else if (effectName == "custom") {
		if (customName != "" &&
			customName != "heart" &&
			customName != "lol" &&
			customName != "matrix" &&
			customName != "plane" &&
			customName != "random" &&
			customName != "sin" &&
			customName != "rain") {
			mutex * m = app->cubesMutex();
			m->lock();

			list<IEffect*> * effects = app->effects();
			list<IEffect*>::iterator etr;
			bool found = false;

			for (etr = effects->begin(); etr != effects->end(); ++etr) {
				IEffect * cur = *etr;
				if (cur->name() == customName)
					found = true;
			}

			if (!found)
				ef = new CustomEffect(customName);
			else
				cout << "Name has to be unique!" << endl;
			
			m->unlock();
		}
		else
			cout << "Name has to be unique!" << endl;
	}
	else
		cout << "Unknown effect name: " << effectName << endl;

	if (ef != NULL) {
		mutex * m = app->cubesMutex();
		m->lock();
		list<IEffect*> * effects = app->effects();
		effects->push_back(ef);
		cout << "New effect has been added: " << effectName << endl;
		m->unlock();
	}

}