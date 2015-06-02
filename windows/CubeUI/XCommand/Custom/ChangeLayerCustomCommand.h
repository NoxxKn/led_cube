#ifndef _CHANGELAYERCUSTOMCOMMAND_H_
#define _CHANGELAYERCUSTOMCOMMAND_H_

#include "../../Command/ICommand.h"

namespace NX {
	class ChangeLayerCustomCommand : public ICommand {
	public:
		ChangeLayerCustomCommand() : ICommand() {

		}

		virtual ~ChangeLayerCustomCommand() {

		}

		virtual void exec();
	};
}

#endif