#ifndef _SETROWLIMITCUSTOMCOMMAND_H_
#define _SETROWLIMITCUSTOMCOMMAND_H_

#include "../../Command/ICommand.h"

namespace NX {
	class SetRowLimitCustomCommand : public ICommand {
	public:
		SetRowLimitCustomCommand() : ICommand() {

		}

		virtual ~SetRowLimitCustomCommand() {

		}

		virtual void exec();
	};
}

#endif