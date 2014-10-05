#ifndef _SHOWCUBESCOMMAND_H_
#define _SHOWCUBESCOMMAND_H_

#include "../../Command/ICommand.h"

namespace NX {
	class ShowCubesCommand : public ICommand {

	public:
		ShowCubesCommand() : ICommand() {
		}

		virtual ~ShowCubesCommand() {

		}

		virtual void exec();
	};
}

#endif