#ifndef _SINEFFECT_H_
#define _SINEFFECT_H_

#include "Effect.h"

namespace NX {
	class SinEffect : public Effect {
	private:
		int mRunner;
	public:
		SinEffect() {
			mRunner = 0;
		}

		virtual ~SinEffect() {

		}

		virtual void run();
	};
}

#endif