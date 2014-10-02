#include <Windows.h>
#include <GL/glut.h>
#include "View.h"
#include "../Application/Application.h"

using namespace std;
using namespace NX;

View::View() : IView() {

}

View::~View() {
    list<IRenderElement*>::iterator itr;
    for(itr = mElements.begin(); itr != mElements.end(); ++itr)
        delete *itr;
    for(itr = mGUIElem.begin(); itr != mGUIElem.end(); ++itr)
        delete *itr;
}

IRenderElement * View::get(size_t pos) {
    if(pos >= mElements.size())
        return NULL;

    list<IRenderElement*>::iterator itr;
    itr = mElements.begin();
    std::advance(itr, pos);
    return *itr;
}

void View::add(IRenderElement * e) {
    mElements.push_back(e);
}

void View::remove(IRenderElement * e) {
    mElements.remove(e);
}

void View::clear() {
    list<IRenderElement*>::iterator itr;
    for(itr = mElements.begin(); itr != mElements.end(); ++itr)
        delete *itr;

    mElements.clear();
}

IRenderElement * View::getGUI(size_t pos) {
    if(pos >= mGUIElem.size())
        return NULL;

    list<IRenderElement*>::iterator itr;
    itr = mGUIElem.begin();
    std::advance(itr, pos);
    return *itr;
}

void View::addGUI(IRenderElement * e) {
    mGUIElem.push_back(e);
}

void View::removeGUI(IRenderElement * e) {
    mGUIElem.remove(e);
}

void View::clearGUI() {
    list<IRenderElement*>::iterator itr;
    for(itr = mGUIElem.begin(); itr != mGUIElem.end(); ++itr)
        delete *itr;

    mGUIElem.clear();
}

void View::ortho() const {
    Application * app = Application::getInstance();
    MainWindow * win = app->window();

    if(mElements.size() == 0) {
        win->ortho();
        return;
    }

    // MainWindow * win = Application::getInstance()->window();

    double left, right, top, bottom, znear, zfar;
    double bufl, bufr, buft, bufb, bufn, buff;

    list<IRenderElement*>::const_iterator itr;
    itr = mElements.begin();
    IRenderElement * e = *itr;
    e->frame(left, right, top, bottom, znear, zfar);
    ++itr;

    while(itr != mElements.end()) {
        e = *itr;

        e->frame(bufl, bufr, buft, bufb, bufn, buff);

		if(bufl < left)
			left = bufl;
		if(bufr > right)
			right = bufr;
		if(buft > top)
			top = buft;
		if(bufb < bottom)
			bottom = bufb;
		if(bufn < znear)
			znear = bufn;
		if(buff > zfar)
			zfar = buff;

        ++itr;
    }

    win->ortho(left, right, top, bottom, znear, zfar);
}

void View::ortho(IRenderElement * e) const {
    double left, right, top, bottom, znear, zfar;
    e->frame(left, right, top, bottom, znear, zfar);

    Application * app = Application::getInstance();
    MainWindow * win = app->window();

    win->ortho(left, right, top, bottom, znear, zfar);
}

void View::init() {

}

void View::render() const {
    Application * app = Application::getInstance();
    MainWindow * win = app->window();
    list<IRenderElement*>::const_iterator itr;

    for(itr = mElements.begin(); itr != mElements.end(); ++itr) {
        IRenderElement * e = *itr;
        e->render();
    }

    win->setOrthographicProjection();

    for(itr = mGUIElem.begin(); itr != mGUIElem.end(); ++itr) {
        IRenderElement * e = *itr;
        e->render();
    }

    win->resetPerspectiveProjection();

}

void View::update(int elapsedTime) {
    list<IRenderElement*>::iterator itr;
    for(itr = mElements.begin(); itr != mElements.end(); ++itr) {
        IRenderElement * e = *itr;
        e->update(elapsedTime);
    }
    for(itr = mGUIElem.begin(); itr != mGUIElem.end(); ++itr) {
        IRenderElement * e = *itr;
        e->update(elapsedTime);
    }
}

void View::uninit() {

}
