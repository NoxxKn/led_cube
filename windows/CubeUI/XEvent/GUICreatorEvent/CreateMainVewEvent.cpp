#include "../../Application/Application.h"
#include "../../View/View.h"
#include "../../Effect/RandomEffect.h"
#include "../../Effect/HeartEffect.h"
#include "../../Effect/SinEffect.h"
#include "CreateMainViewEvent.h"

using namespace std;
using namespace NX;

void CreateMainViewEvent::trigger() {
    // important global variables
    Application * app = Application::getInstance();
    MainWindow * win = app->window();

    // create new view
    IView * view = new View();

    // activate view
    win->changeView(view);

	// create Cube and Effects
	app->addCube(new Cube());
	app->addEffect(new SinEffect());
}
