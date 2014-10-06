#ifndef _LOADCUSTOMCOMMAND_H_
#define _LOADCUSTOMCOMMAND_H_

#include "../../Command/ICommand.h"

namespace NX {
	class LoadCustomCommand : public ICommand {
	public:
		LoadCustomCommand() : ICommand() {

		}

		virtual ~LoadCustomCommand() {

		}

		virtual void exec();
	};
}

#endif