#include <Windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "MainWindow.h"
#include "../Application/Application.h"
#include "../XEvent/MouseEvent/MouseScrollEvent.h"
#include "../XEvent/MouseEvent/MouseWheelEvent.h"

using namespace std;
using namespace NX;

MainWindow::MainWindow() : GLUTWindow() {

}

MainWindow::MainWindow(const int width, const int height,
	const double left, const double right, const double top, const double bottom, const double znear, const double zfar,
	const int posx, const int posy,
	const float clearr, const float clearg, const float clearb, const  float cleara,
	const string & name)
	: GLUTWindow(width, height,
	left, right, top, bottom, znear, zfar,
	posx, posy,
	clearr, clearg, clearb, cleara,
	name) {

}

MainWindow::~MainWindow() {

}

void MainWindow::reset() {

}

void MainWindow::init() {
	glClearColor(mClearR, mClearG, mClearB, mClearA);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
}

void MainWindow::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	if (mView)
		mView->render();
	glutSwapBuffers();
}

void MainWindow::reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(mLeft, mRight, mBottom, mTop, mZNear, mZFar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void MainWindow::timer(int elapsedTime) {
	Application * app = Application::getInstance();
	app->mainloop(elapsedTime);
	if (mView)
		mView->update(elapsedTime);
}

void MainWindow::mouse(int button, int state, int x, int y) {
	static int listenX = 0;
	static int listenY = 0;

	if (button == NX_GL_WHEEL_UP) {
		EventManager::getInstance()->add(new MouseScrollEvent(x, y, true));
		return;
	}
	else if (button == NX_GL_WHEEL_DOWN) {
		EventManager::getInstance()->add(new MouseScrollEvent(x, y, false));
		return;
	}
	else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
		listenX = x;
		listenY = y;
	}
	else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_UP) {
		EventManager::getInstance()->add(new MouseWheelEvent(listenX, listenY, x, y));
	}
}

void MainWindow::keyboard(unsigned char key, int x, int y) {

}

