#include <iostream>
#include "TaskManager.h"

using namespace std;
using namespace NX;

TaskManager * TaskManager::mInstance = NULL;

TaskManager * TaskManager::getInstance() {
	if (mInstance == NULL)
		mInstance = new TaskManager();
	return mInstance;
}

TaskManager::TaskManager() {

}

TaskManager::~TaskManager() {
	list<ITask*>::iterator itr;
	for (itr = mTasks.begin(); itr != mTasks.end(); ++itr) {
		ITask * t = *itr;
		delete t;
	}
	mTasks.clear();
	if (mInstance != NULL)
		mInstance = NULL;
}

void TaskManager::add(ITask *t) {
	mTasks.push_back(t);
}

void TaskManager::remove(ITask *t) {
	mTasks.remove(t);
}

void TaskManager::trigger(int elapsedTime) {
	if (mTasks.size() == 0)
		return;

	ITask * t = *mTasks.begin();
	t->trigger(elapsedTime);
	if (t->isDone()) {
		delete t;
		mTasks.pop_front();
	}
}
