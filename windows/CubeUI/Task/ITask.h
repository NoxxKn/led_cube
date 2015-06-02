#ifndef _ITASK_H_
#define _ITASK_H_

namespace NX {
	class ITask {
	public:
		ITask() {

		}

		virtual ~ITask() {

		}

		virtual bool isDone() const = 0;
		virtual void setDone(const bool done) = 0;
		virtual void trigger(const int elapsedTime) = 0;

	};
}

#endif