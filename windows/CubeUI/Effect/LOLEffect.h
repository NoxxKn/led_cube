#ifndef _LOLEFFECT_H_
#define _LOLEFFECT_H_

#include "Effect.h"

namespace NX {
	class LOLEffect : public Effect {
	private:
		static uint8_t mX1[18];
		static uint8_t mX2[18];
		static uint8_t mY1[18];
		static uint8_t mY2[18];
		static uint8_t mZ[18];

		uint8_t mXRunner;
		uint8_t mYRunner;
		uint8_t mZRunner;

	public:
		LOLEffect() : Effect() {
			mName = "LOL";
			mXRunner = 0;
			mYRunner = 0;
			mZRunner = 0;
			mTimes = 16;
		}

		virtual ~LOLEffect() {

		}

		virtual void run();
	};
}

#endif