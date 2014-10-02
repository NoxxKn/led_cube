#ifndef _EVENTMANAGER_H_
#define _EVENTMANAGER_H_

#include <list>
#include "IEvent.h"

namespace NX {
	class EventManager {
	private:
		static EventManager * mInstance;

		std::list<IEvent*> mEvents;

		EventManager();
	public:
		static EventManager * getInstance();

		~EventManager();

		void add(IEvent * ev);
		void remove(IEvent * ev);
		void trigger();
	};
}

#endif