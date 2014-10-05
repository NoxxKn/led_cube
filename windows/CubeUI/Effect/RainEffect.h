#ifndef _RAINEFFECT_H_
#define _RAINEFFECT_H_

#include <list>
#include "Effect.h"

namespace NX {
	class RainEffect : public Effect {
	private:
		std::list<int> xValues;
		std::list<int> yValues;
		std::list<int> zValues;

	public:
		RainEffect() : Effect() {
			mName = "Rain";
			mTimes = 16;
		}

		virtual ~RainEffect() {

		}

		virtual void run();
	};
}

#endif