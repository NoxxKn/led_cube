#include <algorithm>
#include <string>
#include "AddEffectEvent.h"
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

void AddEffectEvent::trigger() {
	Application * app = Application::getInstance();

	string effectName = mEffectName;
	string customName = mCustomName;

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