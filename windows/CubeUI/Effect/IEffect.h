#ifndef _IEFFECT_H_
#define _IEFFECT_H_

#include "../Cube/CubeControl.h"

namespace NX {
	typedef enum eEffectType {
		ET_CALCULATING,
		ET_CUSTOM
	} EffectType;

	class IEffect {
	public:
		IEffect() {

		}

		virtual ~IEffect() {

		}

		virtual EffectType type() const = 0;
		virtual const std::string & name() const = 0;
		virtual const CubeControl & control() const = 0;
		virtual CubeControl & control() = 0;
		virtual size_t times() const = 0;

		virtual void run() = 0;
	};
}

#endif