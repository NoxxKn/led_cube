#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <list>
#include <mutex>
#include <thread>

#include "../XWindow/MainWindow.h"
#include "../Event/EventManager.h"
#include "../Task/TaskManager.h"
#include "../Command/CommandManager.h"

namespace NX {
	class Application {
	private:
		static Application * mInstance;

		Application();

		MainWindow mWindow;
		EventManager * mEventManager;
		TaskManager * mTaskManager;
		CommandManager * mCommandManager;

		// Thread
		std::thread mThread;
		std::mutex mMutex;

		void regCommands();

	public:
		static Application * getInstance();

		~Application();

		MainWindow * window();
		EventManager * eventManager();
		TaskManager * taskManager();
		CommandManager * commandManager();

		void init();
		void mainloop(const int elapsedTime);
		void reset();

		void lockMutex();
		void unlockMutex();

	};
	std::list<std::string> explode(const std::string & str, const char& ch);
	void cmdThread();
}

#endif