#ifndef _GLUTWINDOW_H_
#define _GLUTWINDOW_H_

#include <iostream>
#include "../View/IView.h"

#define NX_GLUT_WINDOW_NEAR	0.1
#define NX_GLUT_WINDOW_FAR	1000.

#define NX_GL_WHEEL_UP            3
#define NX_GL_WHEEL_DOWN          4

#define NX_APPLICATION_WIDTH      1024
#define NX_APPLICATION_HEIGHT     768
#define NX_APPLICATION_ORTHO_L    0.
#define NX_APPLICATION_ORTHO_R    1024.
#define NX_APPLICATION_ORTHO_T    768.
#define NX_APPLICATION_ORTHO_B    0.
#define NX_APPLICATION_ORTHO_N    -5.
#define NX_APPLICATION_ORTHO_F    5.
#define NX_APPLICATION_POS_X      200
#define NX_APPLICATION_POS_Y      200
#define NX_APPLICATION_CLEAR_R    0.2f
#define NX_APPLICATION_CLEAR_G    0.4f
#define NX_APPLICATION_CLEAR_B    0.2f
#define NX_APPLICATION_CLEAR_A    1.0f

namespace NX {
	class GLUTWindow {
	protected:
		std::string mWindowName;

		int mWidth, mHeight;
		double mLeft, mRight, mTop, mBottom;
		double mZNear, mZFar;
		int mPosX, mPosY;
		float mClearR, mClearG, mClearB, mClearA;
		float mCurZoom;
		float mXPixelFactor, mYPixelFactor;
		double mOrthoGraphicWidth, mOrthoGraphicHeight;

		IView * mView;

	public:
		virtual void init() = 0;
		virtual void render() = 0;
		virtual void reshape(const int w, const int h) = 0;
		virtual void timer(const int elapsedTime) = 0;
		virtual void mouse(const int button, const int state, const int x, const int y) = 0;
		virtual void keyboard(const unsigned char key, const int x, const int y) = 0;

		GLUTWindow();
		GLUTWindow(const int width, const int height,
			const double left, const double right, const double top, const double bottom,
			const double znear, const double zfar,
			const int posx, const int posy,
			const float clearr, const float clearg, const float clearb, const float cleara,
			const std::string & name);
		virtual ~GLUTWindow();

		// Getter
		double left() const;
		double right() const;
		double top() const;
		double bottom() const;
		double znear() const;
		double zfar() const;
		int width() const;
		int height() const;
		int posX() const;
		int posY() const;
		float clearR() const;
		float clearG() const;
		float clearB() const;
		float clearA() const;
		float curZoom() const;
		float xPixelFactor() const;
		float yPixelFactor() const;
		const std::string & windowName() const;
		double orthographicWidth() const;
		double orthographicHeight() const;

		// Setter
		double & left();
		double & right();
		double & top();
		double & bottom();
		double & znear();
		double & zfar();
		int & width();
		int & height();
		int & posX();
		int & posY();
		float & clearR();
		float & clearG();
		float & clearB();
		float & clearA();
		float & curZoom();
		float & xPixelFactor();
		float & yPixelFactor();
		std::string & windowName();
		double & orthographicWidth();
		double & orthographicHeight();
		IView * & view();

		// utility
		void changeView(IView * view);
		void ortho();
		void ortho(const double l, const double r, const double t, const double b, const double n, const double f);
		void setOrthographicProjection() const;
		void resetPerspectiveProjection() const;
		void setOrthographic(const double width, const double height);
	};
}

#endif
