#include "../../Application/Application.h"
#include "MouseScrollEvent.h"

using namespace std;
using namespace NX;

void MouseScrollEvent::trigger() {
    MainWindow * win = Application::getInstance()->window();

    // important informations
    double up = -1;
    double left = win->left();
    double right = win->right();
    double top = win->top();
    double bottom = win->bottom();

    // calculate the "in Map" position
    double x = left + mX * win->xPixelFactor();
    double y = top - mY * win->yPixelFactor();

    // calculate frame distances
    double toRight = right - x;
    double toLeft = x - left;
    double toTop = top - y;
    double toBottom = y - bottom;

    // was wheel down?
    if(!mUp)
        up = 1;

    // calc new values
    toRight = toRight + up* (toRight/10);
    toLeft = toLeft + up* (toLeft/10);
    toTop = toTop + up* (toTop/10);
    toBottom = toBottom + up* (toBottom/10);

    // calculate new frame
    right = toRight + x;
    left = x - toLeft;
    top = toTop + y;
    bottom = y - toBottom;

    // set frame to win
	win->left() = left;
    win->right() = right;
    win->top() = top;
	win->bottom() = bottom;

    // trigger ortho
    win->ortho();
}
