#ifndef _ADDEFFECTCOMMAND_H_
#define _ADDEFFECTCOMMAND_H_

#include "../../Command/ICommand.h"

namespace NX {
	class AddEffectCommand : public ICommand {
	public:
		AddEffectCommand() : ICommand() {
			
		}

		virtual ~AddEffectCommand() {

		}

		virtual void exec();
	};
}

#endif