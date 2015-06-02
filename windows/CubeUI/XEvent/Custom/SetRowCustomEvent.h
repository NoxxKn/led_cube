#ifndef _SETROWCUSTOMEVENT_H_
#define _SETROWCUSTOMEVENT_H_

#include <iostream>
#include "../../Event/IEvent.h"

namespace NX {
	class SetRowCustomEvent : public IEvent {
	private:
		std::string mCustomName;
		size_t mLayer, mVal1, mVal2;
		char mRow;

	public:
		SetRowCustomEvent(std::string customName, size_t layer, size_t val1, size_t val2, char row) : IEvent() {
			mCustomName = customName;
			mLayer = layer;
			mVal1 = val1;
			mVal2 = val2;
			mRow = row;
		}

		virtual ~SetRowCustomEvent() {

		}

		virtual void trigger();
	};
}

#endif