#ifndef _CUSTOMEFFECT_H_
#define _CUSTOMEFFECT_H_

#include <vector>
#include "Effect.h"

namespace NX {
	class CustomEffect : public IEffect {
	private:
		std::vector<CubeControl> mLayers;
		std::string mName;
		CubeControl mControl;
		size_t mRunner;

	public:
		CustomEffect(const std::string & name) : IEffect() {
			mName = name;
			mRunner = 0;
		}

		virtual ~CustomEffect() {

		}

		virtual EffectType type() const {
			return ET_CUSTOM;
		}

		virtual const std::string & name() const {
			return mName;
		}

		virtual const CubeControl & control() const {
			return mControl;
		}

		virtual CubeControl & control() {
			return mControl;
		}

		virtual size_t times() const {
			return mLayers.size();
		}

		virtual const CubeControl & control(size_t layer) const;
		virtual CubeControl & control(size_t layer);

		void setLed(size_t layer, uint8_t xRow = 0, uint8_t yRow = 0, uint8_t zRow = 0);
		void setRowX(size_t layer, uint8_t yRow = 0, uint8_t zRow = 0);
		void setRowY(size_t layer, uint8_t xRow = 0, uint8_t zRow = 0);
		void setRowZ(size_t layer, uint8_t xRow = 0, uint8_t yRow = 0);

		void clearLed(size_t layer, uint8_t xRow = 0, uint8_t yRow = 0, uint8_t zRow = 0);
		void clearRowX(size_t layer, uint8_t yRow = 0, uint8_t zRow = 0);
		void clearRowY(size_t layer, uint8_t xRow = 0, uint8_t zRow = 0);
		void clearRowZ(size_t layer, uint8_t xRow = 0, uint8_t yRow = 0);

		void setPlaneX(size_t layer, uint8_t x);
		void setPlaneY(size_t layer, uint8_t y);
		void setPlaneZ(size_t layer, uint8_t z);

		void setRowX(size_t layer, uint8_t yRow, uint8_t zRow, uint8_t beg, uint8_t end);
		void setRowY(size_t layer, uint8_t xRow, uint8_t zRow, uint8_t beg, uint8_t end);
		void setRowZ(size_t layer, uint8_t xRow, uint8_t yRow, uint8_t beg, uint8_t end);

		void clearAll(size_t layer);

		void addLayer();
		void removeLayer(size_t layer);
		size_t sizeLayers() const;

		virtual void run();
	};
}

#endif