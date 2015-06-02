#ifndef _IRENDERELEMENT_H_
#define _IRENDERELEMENT_H_

namespace NX {

	typedef enum eRenderType {
		RT_EMPTY
	} RenderType;

	class IRenderElement {
	public:
		IRenderElement() {

		}

		virtual ~IRenderElement() {

		}

		virtual RenderType getType() const = 0;
		virtual void render() const = 0;
		virtual void frame(double & l, double & r, double & t, double & b, double & n, double & f) const = 0;
		virtual void update(const int elapsedTime) = 0;
	};
}



#endif
