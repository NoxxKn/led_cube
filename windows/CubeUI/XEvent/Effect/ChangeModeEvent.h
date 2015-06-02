#ifndef _CHANGEMODEEVENT_H_
#define _CHANGEMODEEVENT_H_

#include <iostream>
#include "../../Event/IEvent.h"

namespace NX {
	class ChangeModeEvent : public IEvent {
	private:
		std::string mMode;

	public:
		ChangeModeEvent(std::string mode) : IEvent() {
			mMode = mode;
		}

		virtual ~ChangeModeEvent() {

		}

		virtual void trigger();
	};
}

#endif