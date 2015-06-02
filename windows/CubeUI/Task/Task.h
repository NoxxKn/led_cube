#ifndef _TASK_H_
#define _TASK_H_

#include "ITask.h"

namespace NX {
	class Task : public ITask {
	protected:
		bool mDone;

	public:
		Task();
		virtual ~Task();

		virtual bool isDone() const;
		virtual void setDone(const bool done);
		virtual void trigger(const int elapsedTime) = 0;
	};
}

#endif