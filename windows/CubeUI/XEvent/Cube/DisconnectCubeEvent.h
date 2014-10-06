#ifndef _DISCONNECTCUBEEVENT_H_
#define _DISCONNECTCUBEEVENT_H_

#include "../../Event/IEvent.h"

namespace NX {
	class DisconnectCubeEvent : public IEvent {
	private:
		int mCOMNumber;

	public:
		DisconnectCubeEvent(int comNumber) : IEvent() {
			mCOMNumber = comNumber;
		}

		virtual ~DisconnectCubeEvent() {

		}

		virtual void trigger();
	};
}

#endif