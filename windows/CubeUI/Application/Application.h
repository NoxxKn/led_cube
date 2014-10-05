#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <list>
#include <mutex>
#include <thread>
#include <vector>
#include <atomic>

#include "../Effect/IEffect.h"
#include "../Cube/Cube.h"
#include "../XWindow/MainWindow.h"
#include "../Event/EventManager.h"
#include "../Task/TaskManager.h"
#include "../Command/CommandManager.h"

namespace NX {
	typedef enum ePlayMode {
		PM_EFFECTS,
		PM_CUSTOM
	} PlayMode;

	class Application {
	private:
		// -- Singleton Anti Pattern
		static Application * mInstance;
		Application();

		// -- Threads
		// Command
		std::thread mCommandThread;
		std::mutex mTaskMutex;
		// Writer
		std::thread mWriterThread;
		std::mutex mCubesMutex;
		PlayMode mPlayMode;
		size_t mCustomNum;
		size_t mLayerNum;

		// --  Main 
		// View
		MainWindow mWindow;
		// Manager
		EventManager * mEventManager;
		TaskManager * mTaskManager;
		CommandManager * mCommandManager;
		// Registered Cubes
		std::vector<Cube*> mCubes;

		// -- Writer
		// Effects
		std::list<IEffect*> mEffects;

		// -- Global Thread stop
		std::atomic<bool> mGoon;

		// -- private Functions
		void regCommands();

	public:
		static Application * getInstance();

		~Application();

		MainWindow * window();
		EventManager * eventManager();
		TaskManager * taskManager();
		CommandManager * commandManager();

		void addCube(Cube * cube);
		Cube * cube(size_t pos);
		size_t cubesSize() const;
		void removeCube(int comNumber);
		std::vector<Cube*> * cubes();

		void addEffect(IEffect * ef);
		std::list<IEffect*> copyEffects();
		std::list<IEffect*> * effects();

		std::mutex * taskMutex();
		std::mutex * cubesMutex();

		PlayMode playMode() const;
		void playMode(PlayMode playMode);

		size_t customNum() const;
		void customNum(size_t num);

		size_t layerNum() const;
		void layerNum(size_t num);

		bool goon() const;
		void kill();

		void init();
		void mainloop(const int elapsedTime);
		void reset();
	};
	std::list<std::string> explode(const std::string & str, const char& ch);
	void cmdThread();
	void effThread();
}

#endif