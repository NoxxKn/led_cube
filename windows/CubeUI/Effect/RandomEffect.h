#ifndef _RANDOMEFFECT_H_
#define _RANDOMEFFECT_H_

#include "Effect.h"

namespace NX {
	class RandomEffect : public Effect {
	public:
		RandomEffect() {

		}

		virtual ~RandomEffect() {

		}

		virtual void run();
	};
}

#endif