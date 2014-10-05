#ifndef _SETROWCUSTOMCOMMAND_H_
#define _SETROWCUSTOMCOMMAND_H_

#include "../../Command/ICommand.h"

namespace NX {
	class SetRowCustomCommand : public ICommand {
	public:
		SetRowCustomCommand() : ICommand() {

		}

		virtual ~SetRowCustomCommand() {

		}

		virtual void exec();
	};
}

#endif