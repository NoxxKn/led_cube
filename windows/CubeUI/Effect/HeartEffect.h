#ifndef _HEARTEFFECT_H_
#define _HEARTEFFECT_H_

#include "Effect.h"


namespace NX {
	class HeartEffect : public Effect {
	private:
		static double mX[14];
		static double mY[14];
		static double mZ[14];

		double mRotation;

	public:
		HeartEffect() {
			mRotation = 0;
		}

		virtual ~HeartEffect() {

		}

		virtual void run();
	};
}

#endif