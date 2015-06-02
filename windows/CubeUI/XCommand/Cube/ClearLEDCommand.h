#ifndef _CLEARLEDCOMMAND_H_
#define _CLEARLEDCOMMAND_H_

#include "../../Command/ICommand.h"

namespace NX {
	class ClearLEDCommand : public ICommand {

	public:
		ClearLEDCommand() : ICommand() {
		}

		virtual ~ClearLEDCommand() {

		}

		virtual void exec();
	};
}

#endif