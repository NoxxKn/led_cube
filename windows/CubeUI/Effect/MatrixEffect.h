#ifndef _MATRIXEFFECT_H_
#define _MATRIXEFFECT_H_

#include "Effect.h"

namespace NX {
	class MatrixEffect : public Effect {
	private:
		size_t mRunner;
	public:
		MatrixEffect() {
			mRunner = 0;
		}

		virtual ~MatrixEffect() {

		}

		virtual void run();
	};
}

#endif