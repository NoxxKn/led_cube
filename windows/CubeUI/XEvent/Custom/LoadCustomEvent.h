#ifndef _LOADCUSTOMEVENT_H_
#define _LOADCUSTOMEVENT_H_

#include <iostream>
#include "../../Event/IEvent.h"

namespace NX {
	class LoadCustomEvent : public IEvent {
	private:
		std::string mCustomName;
		std::string mFile;

	public:
		LoadCustomEvent(std::string customName, std::string file) : IEvent() {
			mCustomName = customName;
			mFile = file;
		}

		virtual ~LoadCustomEvent() {

		}

		virtual void trigger();
	};
}

#endif