#ifndef _CLEARROWCUSTOMEVENT_H_
#define _CLEARROWCUSTOMEVENT_H_

#include <iostream>
#include "../../Event/IEvent.h"

namespace NX {
	class ClearRowCustomEvent : public IEvent {
	private:
		std::string mCustomName;
		size_t mLayer, mVal1, mVal2;
		char mRow;

	public:
		ClearRowCustomEvent(std::string customName, size_t layer, size_t val1, size_t val2, char row) : IEvent() {
			mCustomName = customName;
			mLayer = layer;
			mVal1 = val1;
			mVal2 = val2;
			mRow = row;
		}

		virtual ~ClearRowCustomEvent() {

		}

		virtual void trigger();
	};
}

#endif