#ifndef _CHANGECUSTOMCUSTOMCOMMAND_H_
#define _CHANGECUSTOMCUSTOMCOMMAND_H_

#include "../../Command/ICommand.h"

namespace NX {
	class ChangeCustomCustomCommand : public ICommand {
	public:
		ChangeCustomCustomCommand() : ICommand() {

		}

		virtual ~ChangeCustomCustomCommand() {

		}

		virtual void exec();
	};
}

#endif