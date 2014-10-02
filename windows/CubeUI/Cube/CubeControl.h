#ifndef _CUBECONTROLL_H_
#define _CUBECONTROLL_H_

#include <stdint.h>

#define ON	1
#define OFF 0

typedef union uCubeControl {
	uint64_t layer_f[8];
	union {
		uint16_t	tlc[4];
		uint8_t		row[8];
	} layer_d[8];
} CubeControl;

#endif