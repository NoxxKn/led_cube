#include "CommandManager.h"

using namespace std;
using namespace NX;

CommandManager * CommandManager::mInstance = NULL;

CommandManager * CommandManager::getInstance() {
	if (mInstance == NULL)
		mInstance = new CommandManager();
	return mInstance;
}

CommandManager::CommandManager() {

}

CommandManager::~CommandManager() {
	map<string, ICommand*>::iterator itr;
	for (itr = mCommands.begin(); itr != mCommands.end(); ++itr) {
		ICommand * c = itr->second;
		delete c;
	}
	mCommands.clear();
	if (mInstance != NULL)
		mInstance = NULL;
}

bool CommandManager::isCmd(const string & name) const {
	if (mCommands.find(name) != mCommands.end())
		return true;
	return false;
}

void CommandManager::reg(const string & name, ICommand *cmd) {
	mCommands[name] = cmd;
}

ICommand * CommandManager::cmd(const string & name) {
	if (!isCmd(name))
		return mCommands["notfound"];
	return mCommands[name];
}

const list<string> & CommandManager::getLoadValues() const {
	return mValues;
}

void CommandManager::setValues(const list<string> & l) {
	mValues = l;
}

ICommand * & CommandManager::operator[](const std::string & name) {
	if (!isCmd(name))
		return mCommands["notfound"];
	return mCommands[name];
}
