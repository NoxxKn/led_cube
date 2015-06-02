#include <algorithm>
#include "CustomEffect.h"

using namespace std;
using namespace NX;

const CubeControl & CustomEffect::control(size_t layer) const {
	return mLayers[layer];
}

CubeControl & CustomEffect::control(size_t layer) {
	return mLayers[layer];
}

void CustomEffect::clearLed(size_t layer, uint8_t x, uint8_t y, uint8_t z) {
	if (layer >= mLayers.size())
		return;
	mLayers[layer].layer_d[z].row[y] &= ~(1 << x);
}

void CustomEffect::clearRowX(size_t layer, uint8_t y, uint8_t z) {
	if (layer >= mLayers.size())
		return;
	mLayers[layer].layer_d[z].row[y] &= 0x00;
}

void CustomEffect::clearRowY(size_t layer, uint8_t x, uint8_t z) {
	if (layer >= mLayers.size())
		return;
	for (uint8_t i = 0; i < 8; i++)
		mLayers[layer].layer_d[z].row[i] &= ~(1 << x);
}

void CustomEffect::clearRowZ(size_t layer, uint8_t x, uint8_t y) {
	if (layer >= mLayers.size())
		return;
	for (uint8_t i = 0; i < 8; i++)
		mLayers[layer].layer_d[i].row[y] &= ~(1 << x);
}

void CustomEffect::setLed(size_t layer, uint8_t x, uint8_t y, uint8_t z) {
	if (layer >= mLayers.size())
		return;
	mLayers[layer].layer_d[z].row[y] |= (1 << x);
}

void CustomEffect::setRowX(size_t layer, uint8_t y, uint8_t z) {
	if (layer >= mLayers.size())
		return;
	mLayers[layer].layer_d[z].row[y] |= 0xFF;
}

void CustomEffect::setRowY(size_t layer, uint8_t x, uint8_t z) {
	if (layer >= mLayers.size())
		return;
	for (uint8_t i = 0; i < 8; i++)
		mLayers[layer].layer_d[z].row[i] |= (1 << x);
}

void CustomEffect::setRowZ(size_t layer, uint8_t x, uint8_t y) {
	if (layer >= mLayers.size())
		return;
	for (uint8_t i = 0; i < 8; i++)
		mLayers[layer].layer_d[i].row[y] |= (1 << x);
}

void CustomEffect::setRowX(size_t layer, uint8_t y, uint8_t z, uint8_t beg, uint8_t end) {
	if (layer >= mLayers.size())
		return;
	for (uint8_t i = beg; i < end; ++i)
		setLed(layer, i, y, z);
}

void CustomEffect::setRowY(size_t layer, uint8_t x, uint8_t z, uint8_t beg, uint8_t end) {
	if (layer >= mLayers.size())
		return;
	for (uint8_t i = beg; i < end; ++i)
		setLed(layer, x, i, z);
}

void CustomEffect::setRowZ(size_t layer, uint8_t x, uint8_t y, uint8_t beg, uint8_t end) {
	if (layer >= mLayers.size())
		return;
	for (uint8_t i = beg; i < end; ++i)
		setLed(layer, x, y, i);
}

void CustomEffect::setPlaneX(size_t layer, uint8_t x) {
	if (layer >= mLayers.size())
		return;
	for (uint8_t y = 0; y < 8; ++y) {
		for (uint8_t z = 0; z < 8; ++z) {
			setLed(layer, x, y, z);
		}
	}
}

void CustomEffect::setPlaneY(size_t layer, uint8_t y) {
	if (layer >= mLayers.size())
		return;
	for (uint8_t x = 0; x < 8; ++x) {
		for (uint8_t z = 0; z < 8; ++z) {
			setLed(layer, x, y, z);
		}
	}
}

void CustomEffect::setPlaneZ(size_t layer, uint8_t z){
	if (layer >= mLayers.size())
		return;
	for (uint8_t x = 0; x < 8; ++x) {
		for (uint8_t y = 0; y < 8; ++y) {
			setLed(layer, x, y, z);
		}
	}
}

void CustomEffect::clearAll(size_t layer) {
	if (layer >= mLayers.size())
		return;
	for (uint8_t i = 0; i < 8; ++i) {
		mLayers[layer].layer_f[i] = 0;
	}
}

void CustomEffect::addLayer() {
	mLayers.push_back(CubeControl());
}

void CustomEffect::removeLayer(size_t layer) {
	if (layer >= mLayers.size())
		return;
	vector<CubeControl>::iterator itr = mLayers.begin();
	advance(itr, layer);
	mLayers.erase(itr);
}

size_t CustomEffect::sizeLayers() const {
	return mLayers.size();
}

void CustomEffect::run() {
	mControl = mLayers[mRunner];
	mRunner = (mRunner + 1) % mLayers.size();
}