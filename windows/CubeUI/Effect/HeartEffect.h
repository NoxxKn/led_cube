#ifndef _HEARTEFFECT_H_
#define _HEARTEFFECT_H_

#include "Effect.h"


namespace NX {
	class HeartEffect : public Effect {
	private:
		static double mX[14];
		static double mY[14];
		static double mZ[14];

		int mRunner;

	public:
		HeartEffect() : Effect() {
			mName = "Heart";
			mRunner = 0;
			mTimes = 16;
		}

		virtual ~HeartEffect() {

		}

		virtual void run();
	};
}

#endif