#ifndef _ADDLAYERCUSTOMCOMMAND_H_
#define _ADDLAYERCUSTOMCOMMAND_H_

#include "../../Command/ICommand.h"

namespace NX {
	class AddLayerCustomCommand : public ICommand {
	public:
		AddLayerCustomCommand() : ICommand() {

		}

		virtual ~AddLayerCustomCommand() {

		}

		virtual void exec();
	};
}

#endif