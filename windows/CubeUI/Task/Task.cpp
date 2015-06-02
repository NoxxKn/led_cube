#include <iostream>
#include "Task.h"

using namespace std;
using namespace NX;

Task::Task() : ITask() {
	mDone = false;
}

Task::~Task() {

}

bool Task::isDone() const {
	return mDone;
}

void Task::setDone(bool _done) {
	mDone = _done;
}

