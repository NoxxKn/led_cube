#ifndef _SETROWLIMITCUSTOMEVENT_H_
#define _SETROWLIMITCUSTOMEVENT_H_

#include <iostream>
#include "../../Event/IEvent.h"

namespace NX {
	class SetRowLimitCustomEvent : public IEvent {
	private:
		std::string mCustomName;
		size_t mLayer, mVal1, mVal2, mBegin, mEnd;
		char mRow;

	public:
		SetRowLimitCustomEvent(std::string customName, size_t layer, size_t val1, size_t val2, char row, size_t begin, size_t end) : IEvent() {
			mCustomName = customName;
			mLayer = layer;
			mVal1 = val1;
			mVal2 = val2;
			mRow = row;
			mBegin = begin;
			mEnd = end;
		}

		virtual ~SetRowLimitCustomEvent() {

		}

		virtual void trigger();
	};
}

#endif