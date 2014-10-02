#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include "../Window/GLUTWindow.h"

namespace NX {
	class MainWindow : public GLUTWindow {
	public:
		MainWindow();
		MainWindow(const int width, const int height,
			const double left, const double right, const double top, const double bottom,
			const double znear, const double zfar,
			const int posx, const int posy,
			const float clearr, const float clearg, const float clearb, const float cleara,
			const std::string & name);

		virtual ~MainWindow();

		virtual void reset();
		virtual void init();
		virtual void render();
		virtual void reshape(const int w, const int h);
		virtual void timer(const int elapsedTime);
		virtual void mouse(const int button, const int state, const int x, const int y);
		virtual void keyboard(const unsigned char key, const int x, const int y);
	};
}

#endif
