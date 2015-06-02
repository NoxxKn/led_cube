#ifndef _MOUSESCROLLEVENT_H_
#define _MOUSESCROLLEVENT_H_

#include "../../Event/IEvent.h"

namespace NX {
    class MouseScrollEvent : public IEvent {
    private:
        int mX, mY;
        bool mUp;
    public:
        MouseScrollEvent(const int x, const int y, const bool up) : IEvent() {
            mX = x;
            mY = y;
            mUp = up;
        }

        virtual ~MouseScrollEvent() {

        }

        virtual void trigger();
    };
}

#endif

