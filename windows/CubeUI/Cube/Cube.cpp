#include "Cube.h"
#include <iostream>
#include <sstream>

using namespace std;

Cube::Cube(void) {
	cubeConnect(10);
}


Cube::~Cube(void) {
	if (mHandleSerial != INVALID_HANDLE_VALUE)
		CloseHandle(mHandleSerial);
}

void cubeSetLed(uint8_t x, uint8_t y, uint8_t z, bool value, CubeControl * data)
{
	data->layer_d[z].row[y] |= (1 << x);
}

uint8_t cubeRain(CubeControl * data)
{
	int8_t i;
	uint64_t led;

	for (i = 0; i < 7; i++)
	{
		memcpy(&(data->layer_f[i]), &(data->layer_f[i + 1]), sizeof(uint64_t));
	}
	i = 8;
	data->layer_f[7] = 0;
	while (i-- > 0)
	{
		led = 1;
		led <<= rand() % 64;
		data->layer_f[7] |= led;
	}

	return 0;
}

bool Cube::cubeConnect(uint8_t portNum) {
	int size = 0, tmp_port_num = portNum;
	stringstream ss;
	string sFile;
	for (size = 0; tmp_port_num > 0; size++)
		tmp_port_num /= 10;
	
	ss << CUBE_COM_STR;
	ss << static_cast<int>(portNum);
	ss >> sFile;

	mHandleSerial = CreateFile(sFile.c_str(),
		GENERIC_READ | GENERIC_WRITE,
		0,
		0,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		0);

	if (mHandleSerial == INVALID_HANDLE_VALUE) {
		if (GetLastError() == ERROR_FILE_NOT_FOUND) {
			cout << "Serial Port doesn't exist!" << endl;
			return FALSE;
		}
		else {
			cout << "Other failure!" << endl;
			return FALSE;
		}
	}
	else {
		if (!GetCommState(mHandleSerial, &mDCBSerialParams)) {
			cout << "Error getting state!" << endl;
			return FALSE;
		}
	}

#ifdef DEBUG
	cout << "Baudrate: " << dcbSerialParams.BaudRate << endl;
	cout << "Byte Size: " << (int)dcbSerialParams.ByteSize << endl;
	cout << "Stop Bits: " << (int)dcbSerialParams.StopBits << endl;
	cout << "Parity: " << (int)dcbSerialParams.Parity << endl;
#endif
	mDCBSerialParams.BaudRate = CBR_19200;
	mDCBSerialParams.ByteSize = 8;
	mDCBSerialParams.StopBits = ONESTOPBIT;
	mDCBSerialParams.Parity = NOPARITY;
	if (!SetCommState(mHandleSerial, &mDCBSerialParams)){
		cout << "Error set CommState!" << endl;
	}
#ifdef DEBUG
	cout << "Baudrate: " << dcbSerialParams.BaudRate << endl;
	cout << "Byte Size: " << (int)dcbSerialParams.ByteSize << endl;
	cout << "Stop Bits: " << (int)dcbSerialParams.StopBits << endl;
	cout << "Parity: " << (int)dcbSerialParams.Parity << endl;
#endif
	return TRUE;
}

void Cube::clearLed(uint8_t x, uint8_t y, uint8_t z) {
	mControl.layer_d[z].row[y] &= ~(1 << x);
}

void Cube::clearRowX(uint8_t y, uint8_t z) {
	mControl.layer_d[z].row[y] &= 0x00;
}

void Cube::clearRowY(uint8_t x, uint8_t z) {
	for (uint8_t i = 0; i < 8; i++)
		mControl.layer_d[z].row[i] &= ~(1 << x);
}

void Cube::clearRowZ(uint8_t x, uint8_t y) {
	for (uint8_t i = 0; i < 8; i++)
		mControl.layer_d[i].row[y] &= ~(1 << x);
}

void Cube::setLed(uint8_t x, uint8_t y, uint8_t z) {
	mControl.layer_d[z].row[y] |= (1 << x);
}

void Cube::setRowX(uint8_t y, uint8_t z) {
	mControl.layer_d[z].row[y] |= 0xFF;
}

void Cube::setRowY(uint8_t x, uint8_t z) {
	for (uint8_t i = 0; i < 8; i++)
		mControl.layer_d[z].row[i] |= (1 << x);
}

void Cube::setRowZ(uint8_t x, uint8_t y) {
	for (uint8_t i = 0; i < 8; i++)
		mControl.layer_d[i].row[y] |= (1 << x);
}

void Cube::clearAll() {
	for (uint8_t i = 0; i < 8; ++i) {
		mControl.layer_f[i] = 0;
	}
}

void Cube::writeControl() {
	memcpy(mWRBuff, &mControl, sizeof(CubeControl));
	WriteFile(mHandleSerial, "SP", 2, &mDWBytesWrite, NULL);
	WriteFile(mHandleSerial, mWRBuff, CUBE_BUFFER_SIZE, &mDWBytesWrite, NULL);
	WriteFile(mHandleSerial, "E", 1, &mDWBytesWrite, NULL);
	Sleep(100);
}