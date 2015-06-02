#ifndef _CHANGELAYERCUSTOMEVENT_H_
#define _CHANGELAYERCUSTOMEVENT_H_

#include "../../Event/IEvent.h"

namespace NX {
	class ChangeLayerCustomEvent : public IEvent {
	private:
		size_t mLayer;

	public:
		ChangeLayerCustomEvent(size_t layer) : IEvent() {
			mLayer = layer;
		}

		virtual ~ChangeLayerCustomEvent() {

		}

		virtual void trigger();
	};
}

#endif