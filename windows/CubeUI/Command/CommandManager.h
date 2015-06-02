#ifndef _COMMANDMANAGER_H_
#define _COMMANDMANAGER_H_

#include <iostream>
#include <list>
#include <map>
#include "ICommand.h"

namespace NX {
	class CommandManager {
	private:
		static CommandManager * mInstance;
		std::list<std::string> mValues;
		std::map<std::string, ICommand*> mCommands;

		CommandManager();
	public:
		static CommandManager * getInstance();

		~CommandManager();

		bool isCmd(const std::string & name) const;
		void reg(const std::string & name, ICommand * cmd);
		ICommand * cmd(const std::string & name);
		const std::list<std::string> & getLoadValues() const;
		void setValues(const std::list<std::string> & l);
		ICommand * & operator[](const std::string & name);
	};
}

#endif
