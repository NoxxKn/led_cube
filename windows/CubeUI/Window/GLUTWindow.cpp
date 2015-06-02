#include <Windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "GLUTWindow.h"

using namespace std;
using namespace NX;

GLUTWindow::GLUTWindow() {
	mView = NULL;
}

GLUTWindow::GLUTWindow(const int width, const  int height,
	const double left, const  double right, double top, const  double bottom,
	const double znear, const double zfar,
	const int posx, const int posy,
	const float clearr, const float clearg, const float clearb, const float cleara,
	const std::string & name) {
	mWidth = width;
	mHeight = height;
	mLeft = left;
	mRight = right;
	mTop = top;
	mBottom = bottom;
	mZNear = znear;
	mZFar = zfar;
	mPosX = posx;
	mPosY = posy;
	mClearR = clearr;
	mClearG = clearg;
	mClearB = clearb;
	mClearA = cleara;
	mWindowName = name;
	mView = NULL;
	mXPixelFactor = 1;
	mYPixelFactor = 1;
	mOrthoGraphicWidth = static_cast<double>(width);
	mOrthoGraphicHeight = static_cast<double>(height);
}

GLUTWindow::~GLUTWindow() {
	if (mView)
		delete mView;
}

double GLUTWindow::left() const {
	return mLeft;
}

double GLUTWindow::right() const {
	return mRight;
}

double GLUTWindow::top() const {
	return mTop;
}

double GLUTWindow::bottom() const {
	return mBottom;
}

double GLUTWindow::znear() const {
	return mZNear;
}

double GLUTWindow::zfar() const {
	return mZFar;
}

int GLUTWindow::width() const {
	return mWidth;
}

int GLUTWindow::height() const {
	return mHeight;
}

int GLUTWindow::posX() const {
	return mPosX;
}

int GLUTWindow::posY() const {
	return mPosY;
}

float GLUTWindow::clearR() const {
	return mClearR;
}

float GLUTWindow::clearG() const {
	return mClearG;
}

float GLUTWindow::clearB() const {
	return mClearB;
}

float GLUTWindow::clearA() const {
	return mClearA;
}

float GLUTWindow::curZoom() const {
	return mCurZoom;
}

float GLUTWindow::xPixelFactor() const {
	return mXPixelFactor;
}

float GLUTWindow::yPixelFactor() const {
	return mYPixelFactor;
}

const string & GLUTWindow::windowName() const {
	return mWindowName;
}

double GLUTWindow::orthographicWidth() const {
	return mOrthoGraphicWidth;
}

double GLUTWindow::orthographicHeight() const {
	return mOrthoGraphicHeight;
}

double & GLUTWindow::left() {
	return mLeft;
}

double & GLUTWindow::right() {
	return mRight;
}

double & GLUTWindow::top() {
	return mTop;
}

double & GLUTWindow::bottom() {
	return mBottom;
}

double & GLUTWindow::znear() {
	return mZNear;
}

double & GLUTWindow::zfar() {
	return mZFar;
}

int & GLUTWindow::width() {
	return mWidth;
}

int & GLUTWindow::height() {
	return mHeight;
}

int & GLUTWindow::posX() {
	return mPosX;
}

int & GLUTWindow::posY() {
	return mPosY;
}

float & GLUTWindow::clearR() {
	return mClearR;
}

float & GLUTWindow::clearG() {
	return mClearG;
}

float & GLUTWindow::clearB() {
	return mClearB;
}

float & GLUTWindow::clearA() {
	return mClearA;
}

float & GLUTWindow::curZoom() {
	return mCurZoom;
}

float & GLUTWindow::xPixelFactor() {
	return mXPixelFactor;
}

float & GLUTWindow::yPixelFactor() {
	return mYPixelFactor;
}

string & GLUTWindow::windowName() {
	return mWindowName;
}

IView * & GLUTWindow::view() {
	return mView;
}

double & GLUTWindow::orthographicWidth() {
	return mOrthoGraphicWidth;
}

double & GLUTWindow::orthographicHeight() {
	return mOrthoGraphicHeight;
}

void GLUTWindow::changeView(IView * view) {
	if (mView != NULL) {
		mView->uninit();
		delete mView;
	}
	mView = view;
	mView->init();
	mView->ortho();
}

void GLUTWindow::ortho(const double l, const double r, const  double t, const  double b, const double n, const  double f) {
	double resolution = static_cast<double>(mWidth) / static_cast<double>(mHeight);
	double frameWidth = r - l;
	double frameHeight = t - b;
	double frameRes = abs(frameWidth) / abs(frameHeight);
	double rbuf = r, tbuf = t;

	if (resolution > frameRes) {
		// height is greater than usual
		// correct width
		frameWidth = frameHeight * resolution;
		rbuf = l + frameWidth;
	}
	else {
		// width is greater than usual
		// correct height
		frameHeight = frameWidth / resolution;
		tbuf = b + frameHeight;
	}

	mCurZoom = 1.;

	mLeft = l;
	mRight = rbuf;
	mTop = tbuf;
	mBottom = b;

	if (n != 0.)
		mZNear = n;
	else
		mZNear = NX_GLUT_WINDOW_NEAR;

	if (f != 0.)
		mZFar = f;
	else
		mZFar = NX_GLUT_WINDOW_FAR;

	mXPixelFactor = frameWidth / mWidth;
	mYPixelFactor = frameHeight / mHeight;

	glViewport(0, 0, mWidth, mHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(mLeft, mRight, mBottom, mTop, mZNear, mZFar);
	glMatrixMode(GL_MODELVIEW);
}

void GLUTWindow::ortho() {
	double resolution = static_cast<double>(mWidth) / static_cast<double>(mHeight);
	double frameWidth = mRight - mLeft;
	double frameHeight = mTop - mBottom;
	double frameRes = frameWidth / frameHeight;

	if (resolution > frameRes) {
		// height is greater than usual
		// correct width
		frameWidth = frameHeight * resolution;
		mRight = mLeft + frameWidth;
	}
	else {
		// width is greater than usual
		// correct height
		frameHeight = frameWidth / resolution;
		mTop = mBottom + frameHeight;
	}

	mXPixelFactor = frameWidth / mWidth;
	mYPixelFactor = frameHeight / mHeight;

	if (mZNear == 0.)
		mZNear = NX_GLUT_WINDOW_NEAR;
	if (mZFar)
		mZFar = NX_GLUT_WINDOW_FAR;

	glViewport(0, 0, mWidth, mHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// glOrtho(mRight, mLeft, mTop, mBottom, mNear, mFar);
	glOrtho(mLeft, mRight, mBottom, mTop, mZNear, mZFar);
	glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
}

void GLUTWindow::setOrthographicProjection() const {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, mOrthoGraphicWidth, 0, mOrthoGraphicHeight);
	glScalef(1, -1, 1);
	glTranslatef(0, -mOrthoGraphicHeight, 0);
	glMatrixMode(GL_MODELVIEW);
	//
	glPushMatrix();
	glLoadIdentity();
}

void GLUTWindow::resetPerspectiveProjection() const {
	//
	glPopMatrix();
	//
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
}

void GLUTWindow::setOrthographic(const double width, const double height) {
	mOrthoGraphicWidth = width;
	mOrthoGraphicHeight = height;
}
