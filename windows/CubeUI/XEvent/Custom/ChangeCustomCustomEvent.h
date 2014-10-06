#ifndef _CHANGECUSTOMCUSTOMEVENT_H_
#define _CHANGECUSTOMCUSTOMEVENT_H_

#include "../../Event/IEvent.h"

namespace NX {
	class ChangeCustomCustomEvent : public IEvent {
	private:
		size_t mVal;

	public:
		ChangeCustomCustomEvent(size_t val) : IEvent() {
			mVal = val;
		}

		virtual ~ChangeCustomCustomEvent() {

		}

		virtual void trigger();
	};
}

#endif