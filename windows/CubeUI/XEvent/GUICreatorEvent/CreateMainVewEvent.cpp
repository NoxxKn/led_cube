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

    

    // activate view
    win->changeView(view);
}
