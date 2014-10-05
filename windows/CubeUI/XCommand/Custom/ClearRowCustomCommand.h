#ifndef _CLEARROWCUSTOMCOMMAND_H_
#define _CLEARROWCUSTOMCOMMAND_H_

#include "../../Command/ICommand.h"

namespace NX {
	class ClearRowCustomCommand : public ICommand {
	public:
		ClearRowCustomCommand() : ICommand() {

		}

		virtual ~ClearRowCustomCommand() {

		}

		virtual void exec();
	};
}

#endif