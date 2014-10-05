#ifndef _REMOVELAYERCUSTOMCOMMAND_H_
#define _REMOVELAYERCUSTOMCOMMAND_H_

#include "../../Command/ICommand.h"

namespace NX {
	class RemoveLayerCustomCommand : public ICommand {
	public:
		RemoveLayerCustomCommand() : ICommand() {

		}

		virtual ~RemoveLayerCustomCommand() {

		}

		virtual void exec();
	};
}

#endif