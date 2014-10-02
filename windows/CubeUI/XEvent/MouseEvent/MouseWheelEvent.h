#ifndef _MOUSEWHEELEVENT_H_
#define _MOUSEWHEELEVENT_H_

#include "../../Event/IEvent.h"

namespace NX {
    class MouseWheelEvent : public IEvent {
    private:
        int mStartX, mStartY, mEndX, mEndY;
    public:
        MouseWheelEvent(const int startX, const int startY, const int endX, const int endY) : IEvent() {
            mStartX = startX;
            mStartY = startY;
            mEndX = endX;
            mEndY = endY;
        }

        virtual ~MouseWheelEvent() {

        }

        virtual void trigger();
    };
}

#endif

