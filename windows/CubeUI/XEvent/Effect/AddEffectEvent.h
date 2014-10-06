#ifndef _ADDEFFECTEVENT_H_
#define _ADDEFFECTEVENT_H_

#include <iostream>
#include "../../Event/IEvent.h"

namespace NX {
	class AddEffectEvent : public IEvent {
	private:
		std::string mEffectName;
		std::string mCustomName;

	public:
		AddEffectEvent(std::string effectName, std::string customName = "") : IEvent() {
			mEffectName = effectName;
			mCustomName = customName;
		}

		virtual ~AddEffectEvent() {

		}

		virtual void trigger();
	};
}

#endif