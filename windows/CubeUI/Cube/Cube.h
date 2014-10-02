#ifndef _CUBE_H_
#define _CUBE_H_

#define CUBE_BUFFER_SIZE	64
#define CUBE_COM_STR		"\\\\.\\COM"

#include <stdint.h>
#include <windows.h>
#include <conio.h>
#include <atomic>
#include "CubeControl.h"

class Cube {
private:
	std::atomic<CubeControl> mControl;
	bool			mConnected;
	HANDLE			mHandleSerial;
	DCB				mDCBSerialParams;
	char			mWRBuff[CUBE_BUFFER_SIZE + 1];
	DWORD			mDWBytesWrite;

	bool cubeConnect(uint8_t portNum);
	void cubeSetLed(uint8_t x, uint8_t y, uint8_t z, bool value, CubeControl * data);
	uint8_t cubeRain(CubeControl * data);

public:
	Cube();
	~Cube();

	void setLed(uint8_t xRow = 0, uint8_t yRow = 0, uint8_t zRow = 0);
	void setRowX(uint8_t yRow = 0, uint8_t zRow = 0);
	void setRowY(uint8_t xRow = 0, uint8_t zRow = 0);
	void setRowZ(uint8_t xRow = 0, uint8_t yRow = 0);

	void clearLed(uint8_t xRow = 0, uint8_t yRow = 0, uint8_t zRow = 0);
	void clearRowX(uint8_t yRow = 0, uint8_t zRow = 0);
	void clearRowY(uint8_t xRow = 0, uint8_t zRow = 0);
	void clearRowZ(uint8_t xRow = 0, uint8_t yRow = 0);

	void clearAll();

	CubeControl control() const;
	void setControl(const CubeControl & con);

	void writeControl();
};

#endif