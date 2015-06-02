#include "Cube.h"
#include <iostream>
#include <sstream>

using namespace std;

Cube::Cube(void) {
	cubeConnect(9);
}

Cube::~Cube(void) {
	clearAll();
	writeControl();

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

bool Cube::cubeConnect(int portNum, int baudRate, int parityBit, int byteSize, int stopBits) {
	stringstream ss;
	string sFile;
	
	ss << CUBE_COM_STR;
	ss << portNum;
	ss >> sFile;

	mComNum = portNum;

	mHandleSerial = CreateFile(sFile.c_str(),
		GENERIC_READ | GENERIC_WRITE,
		0,
		0,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		0);

	if (mHandleSerial == INVALID_HANDLE_VALUE) {
		DWORD error = GetLastError();
		if (error == ERROR_FILE_NOT_FOUND) {
			cout << "Serial Port doesn't exist!" << endl;
			return FALSE;
		}
		else if (error == ERROR_ACCESS_DENIED) {
			cout << "Access Denied!" << endl;
			return FALSE;
		} 
		else {
			cout << "Error Num:" << error << " Other failure!" << endl;
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
	mDCBSerialParams.BaudRate = static_cast<DWORD>(baudRate);
	mDCBSerialParams.ByteSize = static_cast<uint8_t>(byteSize);
	mDCBSerialParams.StopBits = static_cast<uint8_t>(stopBits);
	mDCBSerialParams.Parity = static_cast<uint8_t>(parityBit);
	if (!SetCommState(mHandleSerial, &mDCBSerialParams)){
		cout << "Error set CommState!" << endl;
	}
#ifdef DEBUG
	cout << "Baudrate: " << dcbSerialParams.BaudRate << endl;
	cout << "Byte Size: " << (int)dcbSerialParams.ByteSize << endl;
	cout << "Stop Bits: " << (int)dcbSerialParams.StopBits << endl;
	cout << "Parity: " << (int)dcbSerialParams.Parity << endl;
#endif
	mConnected = true;
	return TRUE;
}

void Cube::clearLed(uint8_t x, uint8_t y, uint8_t z) {
	CubeControl con = mControl.load();
	con.layer_d[z].row[y] &= ~(1 << x);
	mControl.store(con);
}

void Cube::clearRowX(uint8_t y, uint8_t z) {
	CubeControl con = mControl.load();
	con.layer_d[z].row[y] &= 0x00;
	mControl.store(con);
}

void Cube::clearRowY(uint8_t x, uint8_t z) {
	CubeControl con = mControl.load();
	for (uint8_t i = 0; i < 8; i++)
		con.layer_d[z].row[i] &= ~(1 << x);
	mControl.store(con);
}

void Cube::clearRowZ(uint8_t x, uint8_t y) {
	CubeControl con = mControl.load();
	for (uint8_t i = 0; i < 8; i++)
		con.layer_d[i].row[y] &= ~(1 << x);
	mControl.store(con);
}

void Cube::setLed(uint8_t x, uint8_t y, uint8_t z) {
	CubeControl con = mControl.load();
	con.layer_d[z].row[y] |= (1 << x);
	mControl.store(con);
}

void Cube::setRowX(uint8_t y, uint8_t z) {
	CubeControl con = mControl.load();
	con.layer_d[z].row[y] |= 0xFF;
	mControl.store(con);
}

void Cube::setRowY(uint8_t x, uint8_t z) {
	CubeControl con = mControl.load();
	for (uint8_t i = 0; i < 8; i++)
		con.layer_d[z].row[i] |= (1 << x);
	mControl.store(con);
}

void Cube::setRowZ(uint8_t x, uint8_t y) {
	CubeControl con = mControl.load();
	for (uint8_t i = 0; i < 8; i++)
		con.layer_d[i].row[y] |= (1 << x);
	mControl.store(con);
}

void Cube::clearAll() {
	CubeControl con = mControl.load();
	for (uint8_t i = 0; i < 8; ++i)
		con.layer_f[i] = 0;
	mControl.store(con);
}

void Cube::writeControl() {
	CubeControl con = mControl.load();
	memcpy(mWRBuff, &con, sizeof(CubeControl));
	WriteFile(mHandleSerial, "SP", 2, &mDWBytesWrite, NULL);
	WriteFile(mHandleSerial, mWRBuff, CUBE_BUFFER_SIZE, &mDWBytesWrite, NULL);
	WriteFile(mHandleSerial, "E", 1, &mDWBytesWrite, NULL);
	Sleep(100);
}

CubeControl Cube::control() const {
	return mControl.load();
}

void Cube::setControl(const CubeControl & con) {
	mControl.store(con);
}

int Cube::comNum() const {
	return mComNum;
}