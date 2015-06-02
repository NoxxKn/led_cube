#ifndef _CLEARLAYERCUSTOMEVENT_H_
#define _CLEARLAYERCUSTOMEVENT_H_

#include <iostream>
#include "../../Event/IEvent.h"

namespace NX {
	class ClearLayerCustomEvent : public IEvent {
	private:
		std::string mCustomName;
		size_t mLayer;

	public:
		ClearLayerCustomEvent(std::string customName, size_t layer) : IEvent() {
			mCustomName = customName;
			mLayer = layer;
		}

		virtual ~ClearLayerCustomEvent() {

		}

		virtual void trigger();
	};
}

#endif