#ifndef _CLEARLEDCUSTOMEVENT_H_
#define _CLEARLEDCUSTOMEVENT_H_

#include <iostream>
#include "../../Event/IEvent.h"

namespace NX {
	class ClearLedCustomEvent : public IEvent {
	private:
		std::string mCustomName;
		size_t mLayer, mX, mY, mZ;

	public:
		ClearLedCustomEvent(std::string customName, size_t layer, size_t x, size_t y, size_t z) : IEvent() {
			mCustomName = customName;
			mLayer = layer;
			mX = x;
			mY = y;
			mZ = z;
		}

		virtual ~ClearLedCustomEvent() {

		}

		virtual void trigger();
	};
}

#endif