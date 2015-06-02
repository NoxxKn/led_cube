#ifndef _REMOVELAYERCUSTOMEVENT_H_
#define _REMOVELAYERCUSTOMEVENT_H_

#include <iostream>
#include "../../Event/IEvent.h"

namespace NX {
	class RemoveLayerCustomEvent : public IEvent {
	private:
		std::string mCustomName;
		size_t mLayer;

	public:
		RemoveLayerCustomEvent(std::string customName, size_t layer) : IEvent() {
			mCustomName = customName;
			mLayer = layer;
		}

		virtual ~RemoveLayerCustomEvent() {

		}

		virtual void trigger();
	};
}

#endif