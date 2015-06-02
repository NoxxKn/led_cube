#ifndef _CLEARLEDEVENT_H_
#define _CLEARLEDEVENT_H_

#include "../../Event/IEvent.h"

namespace NX {
	class ClearLEDEvent : public IEvent {
	private:
		int mCOMNumber;

	public:
		ClearLEDEvent(int comNumber) : IEvent() {
			mCOMNumber = comNumber;
		}

		virtual ~ClearLEDEvent() {

		}

		virtual void trigger();
	};
}

#endif