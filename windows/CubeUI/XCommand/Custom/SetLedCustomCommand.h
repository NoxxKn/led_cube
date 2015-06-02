#ifndef _SETLEDCUSTOMCOMMAND_H_
#define _SETLEDCUSTOMCOMMAND_H_

#include "../../Command/ICommand.h"

namespace NX {
	class SetLedCustomCommand : public ICommand {
	public:
		SetLedCustomCommand() : ICommand() {

		}

		virtual ~SetLedCustomCommand() {

		}

		virtual void exec();
	};
}

#endif