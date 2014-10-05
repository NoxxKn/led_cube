#ifndef _CHANGEMODECOMMAND_H_
#define _CHANGEMODECOMMAND_H_

#include "../../Command/ICommand.h"

namespace NX {
	class ChangeModeCommand : public ICommand {
	public:
		ChangeModeCommand() : ICommand() {

		}

		virtual ~ChangeModeCommand() {

		}

		virtual void exec();
	};
}

#endif