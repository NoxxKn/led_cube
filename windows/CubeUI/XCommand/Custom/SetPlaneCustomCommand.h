#ifndef _SETPLANECUSTOMCOMMAND_H_
#define _SETPLANECUSTOMCOMMAND_H_

#include "../../Command/ICommand.h"

namespace NX {
	class SetPlaneCustomCommand : public ICommand {
	public:
		SetPlaneCustomCommand() : ICommand() {

		}

		virtual ~SetPlaneCustomCommand() {

		}

		virtual void exec();
	};
}

#endif