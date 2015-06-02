#ifndef _CREATEMAINVIEWEVENT_H_
#define _CREATEMAINVIEWEVENT_H_

#include "../../Event/IEvent.h"

namespace NX {
    class CreateMainViewEvent : public IEvent {
    public:
        CreateMainViewEvent() : IEvent() {

        }

        virtual ~CreateMainViewEvent() {

        }

        virtual void trigger();
    };
}

#endif
