#ifndef _IEVENT_H_
#define _IEVENT_H_

namespace NX {
	class IEvent {
	public:
		IEvent() {

		}

		virtual ~IEvent() {

		}

		virtual void trigger() = 0;
	};
}

#endif