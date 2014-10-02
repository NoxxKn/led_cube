#include "../../Application/Application.h"
#include "../../View/View.h"
#include "CreateMainViewEvent.h"

using namespace std;
using namespace NX;

void CreateMainViewEvent::trigger() {
    // important global variables
    Application * app = Application::getInstance();
    MainWindow * win = app->window();

    // create new view
    IView * view = new View();

    // Give Cube crazy shit!
	Cube * cube = app->cubePtr();
	cube->writeControl();

	cube->clearAll();
	cube->writeControl();

	for (int i = 0; i < 100; ++i) {
		int x, y, z;

		cube->clearAll();

		for (int j = 0; j < 10; ++j) {
			x = rand() % 8;
			y = rand() % 8;
			z = rand() % 8;
			cube->setLed(x, y, z);
		}
		cube->writeControl();
	}

	cube->clearAll();
	cube->writeControl();

    // activate view
    win->changeView(view);
}
