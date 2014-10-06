#ifndef _SHOWCUBESEVENT_H_
#define _SHOWCUBESEVENT_H_

#include "../../Event/IEvent.h"

namespace NX {
	class ShowCubesEvent : public IEvent {
	public:
		ShowCubesEvent() : IEvent() {
		}

		virtual ~ShowCubesEvent() {

		}

		virtual void trigger();
	};
}

#endif