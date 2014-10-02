#ifndef _TASKMANAGER_H_
#define _TASKMANAGER_H_

#include <list>
#include "ITask.h"

namespace NX {
	class TaskManager {
	private:
		static TaskManager * mInstance;
		std::list<ITask*> mTasks;

		TaskManager();

	public:
		static TaskManager * getInstance();

		~TaskManager();

		void add(ITask * t);
		void remove(ITask * t);
		void trigger(const int elapsedTime);
	};
}

#endif
