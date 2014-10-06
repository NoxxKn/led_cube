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
	mMutex.lock();
	list<IEvent*>::iterator itr;
	for (itr = mEvents.begin(); itr != mEvents.end(); ++itr) {
		IEvent * ev = *itr;
		delete ev;
	}
	mEvents.clear();
	if (mInstance != NULL)
		mInstance = NULL;
	mMutex.unlock();
}

void EventManager::add(IEvent *ev) {
	mMutex.lock();
	mEvents.push_back(ev);
	mMutex.unlock();
}

void EventManager::remove(IEvent *ev) {
	mMutex.lock();
	mEvents.remove(ev);
	mMutex.unlock();
}

void EventManager::trigger() {
	mMutex.lock();
	list<IEvent*>::iterator itr;
	for (itr = mEvents.begin(); itr != mEvents.end(); ++itr) {
		IEvent * ev = *itr;
		ev->trigger();
		delete ev;
	}
	mEvents.clear();
	mMutex.unlock();
}
