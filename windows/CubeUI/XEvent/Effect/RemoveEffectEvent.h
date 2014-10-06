#ifndef _REMOVEEFFECTEVENT_H_
#define _REMOVEEFFECTEVENT_H_

#include <iostream>
#include "../../Event/IEvent.h"

namespace NX {
	class RemoveEffectEvent : public IEvent {
	private:
		std::string mEffectName;

	public:
		RemoveEffectEvent(std::string effectName) : IEvent() {
			mEffectName = effectName;
		}

		virtual ~RemoveEffectEvent() {

		}

		virtual void trigger();
	};
}

#endif