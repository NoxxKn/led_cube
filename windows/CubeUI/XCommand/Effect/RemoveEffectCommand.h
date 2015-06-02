#ifndef _REMOVEEFFECTCOMMAND_H_
#define _REMOVEEFFECTCOMMAND_H_

#include "../../Command/ICommand.h"

namespace NX {
	class RemoveEffectCommand : public ICommand {
	public:
		RemoveEffectCommand() : ICommand() {
			
		}

		virtual ~RemoveEffectCommand() {

		}

		virtual void exec();
	};
}

#endif