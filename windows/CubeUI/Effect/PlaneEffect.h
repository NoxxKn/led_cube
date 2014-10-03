#ifndef _PLANEEFFECT_H_
#define _PLANEEFFECT_H_

#include "Effect.h"

namespace NX {
	class PlaneEffect : public Effect {
	private:
		size_t mRunner;
	public:
		PlaneEffect() {
			mRunner = 0;
		}

		virtual ~PlaneEffect() {

		}

		virtual void run();
	};
}

#endif