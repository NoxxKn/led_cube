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

	protected:
		std::string mName;
		size_t mTimes;

	public:
		Effect();
		virtual ~Effect();

		virtual EffectType type() const {
			return ET_CALCULATING;
		}

		virtual const std::string & name() const {
			return mName;
		}

		virtual size_t times() const {
			return mTimes;
		}

		void setLed(uint8_t xRow = 0, uint8_t yRow = 0, uint8_t zRow = 0);
		void setRowX(uint8_t yRow = 0, uint8_t zRow = 0);
		void setRowY(uint8_t xRow = 0, uint8_t zRow = 0);
		void setRowZ(uint8_t xRow = 0, uint8_t yRow = 0);

		void clearLed(uint8_t xRow = 0, uint8_t yRow = 0, uint8_t zRow = 0);
		void clearRowX(uint8_t yRow = 0, uint8_t zRow = 0);
		void clearRowY(uint8_t xRow = 0, uint8_t zRow = 0);
		void clearRowZ(uint8_t xRow = 0, uint8_t yRow = 0);

		void setPlaneX(uint8_t x);
		void setPlaneY(uint8_t y);
		void setPlaneZ(uint8_t z);

		void setRowX(uint8_t yRow, uint8_t zRow, uint8_t beg, uint8_t end);
		void setRowY(uint8_t xRow, uint8_t zRow, uint8_t beg, uint8_t end);
		void setRowZ(uint8_t xRow, uint8_t yRow, uint8_t beg, uint8_t end);

		void clearAll();

		virtual const CubeControl & control() const;
		virtual CubeControl & control();

		virtual void run() = 0;
	};
}

#endif