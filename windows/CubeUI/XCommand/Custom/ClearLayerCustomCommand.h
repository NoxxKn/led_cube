#ifndef _CLEARLAYERCUSTOMCOMMAND_H_
#define _CLEARLAYERCUSTOMCOMMAND_H_

#include "../../Command/ICommand.h"

namespace NX {
	class ClearLayerCustomCommand : public ICommand {
	public:
		ClearLayerCustomCommand() : ICommand() {

		}

		virtual ~ClearLayerCustomCommand() {

		}

		virtual void exec();
	};
}

#endif