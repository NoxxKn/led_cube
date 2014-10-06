#ifndef _ADDLAYERCUSTOMEVENT_H_
#define _ADDLAYERCUSTOMEVENT_H_

#include <iostream>
#include "../../Event/IEvent.h"

namespace NX {
	class AddLayerCustomEvent : public IEvent {
	private:
		std::string mCustomName;

	public:
		AddLayerCustomEvent(std::string customName) : IEvent() {
			mCustomName = customName;
		}

		virtual ~AddLayerCustomEvent() {

		}

		virtual void trigger();
	};
}

#endif