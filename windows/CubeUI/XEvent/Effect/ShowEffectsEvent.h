#ifndef _SHOWEFFECTSEVENT_H_
#define _SHOWEFFECTSEVENT_H_

#include "../../Event/IEvent.h"

namespace NX {
	class ShowEffectsEvent : public IEvent {
	public:
		ShowEffectsEvent() : IEvent() {

		}

		virtual ~ShowEffectsEvent() {

		}

		virtual void trigger();
	};
}

#endif