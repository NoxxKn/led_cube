#ifndef _CONNECTCUBECOMMAND_H_
#define _CONNECTCUBECOMMAND_H_

#include "../../Command/ICommand.h"

namespace NX {
	class ConnectCubeCommand : public ICommand {
	private:
		int mCOMNumber;
		int mBaudRate;
		int mParityBit;
		int mByteSize;
		int mStopBits;

	public:
		ConnectCubeCommand(int comNumber = 0, int baudRate = 19200, int parityBit = 0, int byteSize = 8, int stopBits = 0) : ICommand() {
			mCOMNumber = comNumber;
			mBaudRate = baudRate;
			mParityBit = parityBit;
			mByteSize = byteSize;
			mStopBits = stopBits;
		}

		virtual ~ConnectCubeCommand() {

		}

		virtual void exec();
	};
}

#endif