#ifndef _MATRIXEFFECT_H_
#define _MATRIXEFFECT_H_

#include "Effect.h"

namespace NX {
	class MatrixEffect : public Effect {
	private:
		size_t mRunner;
		size_t mEqualizer;
	public:
		MatrixEffect() : Effect() {
			mName = "Matrix";
			mRunner = 0;
			mEqualizer = 0;
			mTimes = 8 + 6 + 4 + 2;
		}

		virtual ~MatrixEffect() {

		}

		virtual void run();
	};
}

#endif