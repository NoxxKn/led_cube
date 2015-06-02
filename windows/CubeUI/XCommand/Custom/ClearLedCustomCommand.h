#ifndef _CLEARLEDCUSTOMCOMMAND_H_
#define _CLEARLEDCUSTOMCOMMAND_H_

#include "../../Command/ICommand.h"

namespace NX {
	class ClearLedCustomCommand : public ICommand {
	public:
		ClearLedCustomCommand() : ICommand() {

		}

		virtual ~ClearLedCustomCommand() {

		}

		virtual void exec();
	};
}

#endif