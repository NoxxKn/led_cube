#ifndef _SETLEDCUSTOMEVENT_H_
#define _SETLEDCUSTOMEVENT_H_

#include <iostream>
#include "../../Event/IEvent.h"

namespace NX {
	class SetLedCustomEvent : public IEvent {
	private:
		std::string mCustomName;
		size_t mLayer, mX, mY, mZ;

	public:
		SetLedCustomEvent(std::string customName, size_t layer, size_t x, size_t y, size_t z) : IEvent() {
			mCustomName = customName;
			mLayer = layer;
			mX = x;
			mY = y;
			mZ = z;
		}

		virtual ~SetLedCustomEvent() {

		}

		virtual void trigger();
	};
}

#endif