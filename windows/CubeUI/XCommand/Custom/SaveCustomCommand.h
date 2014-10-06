#ifndef _SAVECUSTOMCOMMAND_H_
#define _SAVECUSTOMCOMMAND_H_

#include "../../Command/ICommand.h"

namespace NX {
	class SaveCustomCommand : public ICommand {
	public:
		SaveCustomCommand() : ICommand() {

		}

		virtual ~SaveCustomCommand() {

		}

		virtual void exec();
	};
}

#endif