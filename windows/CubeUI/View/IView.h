#ifndef _IVIEW_H_
#define _IVIEW_H_

#include "IRenderElement.h"

namespace NX {
	class IView {
	public:
		IView() {

		}

		virtual ~IView() {

		}

		virtual IRenderElement * get(const size_t pos) = 0;
		virtual void add(IRenderElement * e) = 0;
		virtual void remove(IRenderElement * e) = 0;
		virtual void clear() = 0;

		virtual IRenderElement * getGUI(const size_t pos) = 0;
		virtual void addGUI(IRenderElement * e) = 0;
		virtual void removeGUI(IRenderElement * e) = 0;
		virtual void clearGUI() = 0;

		virtual void ortho() const = 0;
		virtual void ortho(IRenderElement * e) const = 0;
		virtual void init() = 0;
		virtual void render() const = 0;
		virtual void update(const int elapsedTime) = 0;
		virtual void uninit() = 0;
	};
}

#endif