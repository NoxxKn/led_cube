#include <iostream>
#include <Windows.h>
#include <GL\glut.h>
#include "Application\Application.h"

using namespace std;
using namespace NX;

void timer(int value) {
	MainWindow * win = Application::getInstance()->window();
	win->timer(value);
	glutPostRedisplay();
	glutTimerFunc(value, timer, value);
}

void mouse(int button, int state, int x, int y) {
	MainWindow * win = Application::getInstance()->window();
	win->mouse(button, state, x, y);
}

void keyboard(unsigned char key, int x, int y) {
	MainWindow * win = Application::getInstance()->window();
	win->keyboard(key, x, y);
}

void render() {
	MainWindow * win = Application::getInstance()->window();
	win->render();
}

void reshape(int w, int h) {
	MainWindow * win = Application::getInstance()->window();
	win->reshape(w, h);
}

int main(int argc, char ** argv) {
	Application * app = Application::getInstance();
	MainWindow * win = app->window();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(win->width(), win->height());
	glutInitWindowPosition(win->posX(), win->posY());
	glutCreateWindow(win->windowName().c_str());
	app->init();
	win->init();
	glutDisplayFunc(render);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(25, timer, 25);
	glutMainLoop();

	delete app;
	return 0;
}