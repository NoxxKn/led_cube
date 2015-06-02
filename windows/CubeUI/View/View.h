#ifndef _VIEW_H_
#define _VIEW_H_

#include <list>
#include "IRenderElement.h"
#include "IView.h"

namespace NX {
    class View : public IView {
    private:
        std::list<IRenderElement*> mElements;
        std::list<IRenderElement*> mGUIElem;

    public:
        View();
        virtual ~View();

        virtual IRenderElement * get(const size_t pos);
        virtual void add(IRenderElement * e);
        virtual void remove(IRenderElement * e);
        virtual void clear();

        virtual IRenderElement * getGUI(const size_t pos);
        virtual void addGUI(IRenderElement * e);
        virtual void removeGUI(IRenderElement * e);
        virtual void clearGUI();

        virtual void ortho() const;
        virtual void ortho(IRenderElement * e) const;
        virtual void init();
        virtual void render() const;
        virtual void update(const int elapsedTime);
        virtual void uninit();
    };
}

#endif
