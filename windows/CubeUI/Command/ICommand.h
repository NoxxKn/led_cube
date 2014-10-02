#ifndef _ICOMMAND_H_
#define _ICOMMAND_H_

namespace NX {
	class ICommand {
	public:
		ICommand() {

		}

		virtual ~ICommand() {

		}

		virtual void exec() = 0;
	};
}

#endif