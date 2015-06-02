#ifndef _SHOWEFFECTSCOMMAND_H_
#define _SHOWEFFECTSCOMMAND_H_

#include "../../Command/ICommand.h"

namespace NX {
	class ShowEffectsCommand : public ICommand {
	public:
		ShowEffectsCommand() : ICommand() {

		}

		virtual ~ShowEffectsCommand() {

		}

		virtual void exec();
	};
}

#endif