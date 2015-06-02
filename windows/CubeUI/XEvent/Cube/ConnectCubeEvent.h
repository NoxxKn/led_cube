#ifndef _CONNECTCUBEEVENT_H_
#define _CONNECTCUBEEVENT_H_

#include "../../Event/IEvent.h"

namespace NX {
	class ConnectCubeEvent : public IEvent {
	private:
		int mCOMNumber;
		int mBaudRate;
		int mParityBit;
		int mByteSize;
		int mStopBits;

	public:
		ConnectCubeEvent(int comNumber = 0, int baudRate = 19200, int parityBit = 0, int byteSize = 8, int stopBits = 0) : IEvent() {
			mCOMNumber = comNumber;
			mBaudRate = baudRate;
			mParityBit = parityBit;
			mByteSize = byteSize;
			mStopBits = stopBits;
		}

		virtual ~ConnectCubeEvent() {

		}

		virtual void trigger();
	};
}

#endif