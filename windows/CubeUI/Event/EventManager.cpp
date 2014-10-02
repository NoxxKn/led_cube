#include <iostream>
#include "EventManager.h"

using namespace std;
using namespace NX;

EventManager * EventManager::mInstance = NULL;

EventManager * EventManager::getInstance() {
	if (mInstance == NULL)
		mInstance = new EventManager();
	return mInstance;
}


EventManager::EventManager() {

}

EventManager::~EventManager() {
	list<IEvent*>::iterator itr;
	for (itr = mEvents.begin(); itr != mEvents.end(); ++itr) {
		IEvent * ev = *itr;
		delete ev;
	}
	mEvents.clear();
	if (mInstance != NULL)
		mInstance = NULL;
}

void EventManager::add(IEvent *ev) {
	mEvents.push_back(ev);
}

void EventManager::remove(IEvent *ev) {
	mEvents.remove(ev);
}

void EventManager::trigger() {
	list<IEvent*>::iterator itr;
	for (itr = mEvents.begin(); itr != mEvents.end(); ++itr) {
		IEvent * ev = *itr;
		ev->trigger();
		delete ev;
	}
	mEvents.clear();
}
