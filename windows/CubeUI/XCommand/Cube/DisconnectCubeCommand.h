#ifndef _DISCONNECTCUBECOMMAND_H_
#define _DISCONNECTCUBECOMMAND_H_

#include "../../Command/ICommand.h"

namespace NX {
	class DisconnectCubeCommand : public ICommand {

	public:
		DisconnectCubeCommand() : ICommand() {
		}

		virtual ~DisconnectCubeCommand() {

		}

		virtual void exec();
	};
}

#endif