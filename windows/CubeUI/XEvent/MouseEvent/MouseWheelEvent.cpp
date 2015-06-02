#include "../../Application/Application.h"
#include "MouseWheelEvent.h"

using namespace std;
using namespace NX;

void MouseWheelEvent::trigger() {
    MainWindow * win = Application::getInstance()->window();

    // important informations
    double left = win->left();
    double right = win->right();
    double top = win->top();
    double bottom = win->bottom();

    // translate to map postions
    double startx = left + mStartX * win->xPixelFactor();
    double starty = top - mStartY * win->yPixelFactor();
    double endx = left + mEndX * win->xPixelFactor();
    double endy = top - mEndY * win->yPixelFactor();

    // calculate distances
    double xMove = endx - startx;
    double yMove = endy - starty;

    // calculate new frame
    left -= xMove;
    right -= xMove;
    top -= yMove;
    bottom -= yMove;

    // set frame to win
    win->left() = left;
    win->right() = right;
    win->top() = top;
    win->bottom() = bottom;

    // trigger ortho
    win->ortho();
}
