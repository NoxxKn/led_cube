#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "IEffect.h"

#define EFFECT_DELAY 100

namespace NX {
	class Effect : public IEffect {
	private:
		const int mDelay = EFFECT_DELAY;

		CubeControl mControl;

		virtual void delay() const;

	public:
		Effect();
		virtual ~Effect();

		void setLed(uint8_t xRow = 0, uint8_t yRow = 0, uint8_t zRow = 0);
		void setRowX(uint8_t yRow = 0, uint8_t zRow = 0);
		void setRowY(uint8_t xRow = 0, uint8_t zRow = 0);
		void setRowZ(uint8_t xRow = 0, uint8_t yRow = 0);

		void clearLed(uint8_t xRow = 0, uint8_t yRow = 0, uint8_t zRow = 0);
		void clearRowX(uint8_t yRow = 0, uint8_t zRow = 0);
		void clearRowY(uint8_t xRow = 0, uint8_t zRow = 0);
		void clearRowZ(uint8_t xRow = 0, uint8_t yRow = 0);

		void clearAll();

		virtual const CubeControl & control() const;
		virtual CubeControl & control();

		virtual void run() = 0;
	};
}

#endif