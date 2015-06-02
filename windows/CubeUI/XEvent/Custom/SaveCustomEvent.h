#ifndef _SAVECUSTOMEVENT_H_
#define _SAVECUSTOMEVENT_H_

#include <iostream>
#include "../../Event/IEvent.h"

namespace NX {
	class SaveCustomEvent : public IEvent {
	private:
		std::string mFileName;
		std::string mCustomName;

	public:
		SaveCustomEvent(std::string fileName, std::string customName) : IEvent() {
			mFileName = fileName;
			mCustomName = customName;
		}

		virtual ~SaveCustomEvent() {

		}

		virtual void trigger();
	};
}

#endif