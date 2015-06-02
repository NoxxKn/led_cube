#ifndef _SETPLANECUSTOMEVENT_H_
#define _SETPLANECUSTOMEVENT_H_

#include <iostream>
#include "../../Event/IEvent.h"

namespace NX {
	class SetPlaneCustomEvent : public IEvent {
	private:
		std::string mCustomName;
		size_t mLayer, mVal;
		char mRow;

	public:
		SetPlaneCustomEvent(std::string customName, size_t layer, size_t val, char row) : IEvent() {
			mCustomName = customName;
			mLayer = layer;
			mVal = val;
			mRow = row;
		}

		virtual ~SetPlaneCustomEvent() {

		}

		virtual void trigger();
	};
}

#endif