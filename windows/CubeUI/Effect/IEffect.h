#ifndef _IEFFECT_H_
#define _IEFFECT_H_

#include "../Cube/CubeControl.h"

namespace NX {
	class IEffect {
	public:
		IEffect() {

		}

		virtual ~IEffect() {

		}

		virtual const CubeControl & control() const = 0;
		virtual CubeControl & control() = 0;

		virtual void run() = 0;
	};
}

#endif