#include <iostream>
#include <windows.h>
#include "Effect.h"

using namespace std;
using namespace NX;

Effect::Effect() : IEffect() {
	mName = "";
	mTimes = 0;
}

Effect::~Effect() {

}

void Effect::delay() const {
	Sleep(mDelay);
}

void Effect::clearLed(uint8_t x, uint8_t y, uint8_t z) {
	mControl.layer_d[z].row[y] &= ~(1 << x);
}

void Effect::clearRowX(uint8_t y, uint8_t z) {
	mControl.layer_d[z].row[y] &= 0x00;
}

void Effect::clearRowY(uint8_t x, uint8_t z) {
	for (uint8_t i = 0; i < 8; i++)
		mControl.layer_d[z].row[i] &= ~(1 << x);
}

void Effect::clearRowZ(uint8_t x, uint8_t y) {
	for (uint8_t i = 0; i < 8; i++)
		mControl.layer_d[i].row[y] &= ~(1 << x);
}

void Effect::setLed(uint8_t x, uint8_t y, uint8_t z) {
	mControl.layer_d[z].row[y] |= (1 << x);
}

void Effect::setRowX(uint8_t y, uint8_t z) {
	mControl.layer_d[z].row[y] |= 0xFF;
}

void Effect::setRowY(uint8_t x, uint8_t z) {
	for (uint8_t i = 0; i < 8; i++)
		mControl.layer_d[z].row[i] |= (1 << x);
}

void Effect::setRowZ(uint8_t x, uint8_t y) {
	for (uint8_t i = 0; i < 8; i++)
		mControl.layer_d[i].row[y] |= (1 << x);
}

void Effect::setRowX(uint8_t y, uint8_t z, uint8_t beg, uint8_t end) {
	for (uint8_t i = beg; i < end; ++i)
		setLed(i, y, z);
}

void Effect::setRowY(uint8_t x, uint8_t z, uint8_t beg, uint8_t end) {
	for (uint8_t i = beg; i < end; ++i)
		setLed(x, i, z);
}

void Effect::setRowZ(uint8_t x, uint8_t y, uint8_t beg, uint8_t end) {
	for (uint8_t i = beg; i < end; ++i)
		setLed(x, y, i);
}

void Effect::setPlaneX(uint8_t x) {
	for (uint8_t y = 0; y < 8; ++y) {
		for (uint8_t z = 0; z < 8; ++z) {
			setLed(x, y, z);
		}
	}
}

void Effect::setPlaneY(uint8_t y) {
	for (uint8_t x = 0; x < 8; ++x) {
		for (uint8_t z = 0; z < 8; ++z) {
			setLed(x, y, z);
		}
	}
}

void Effect::setPlaneZ(uint8_t z){
	for (uint8_t x = 0; x < 8; ++x) {
		for (uint8_t y = 0; y < 8; ++y) {
			setLed(x, y, z);
		}
	}
}

void Effect::clearAll() {
	for (uint8_t i = 0; i < 8; ++i) {
		mControl.layer_f[i] = 0;
	}
}

CubeControl & Effect::control() {
	return mControl;
}

const CubeControl & Effect::control() const {
	return mControl;
}