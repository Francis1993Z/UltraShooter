#ifndef WIDGETLISTENER_INCLUDED_HPP
#define WIDGETLISTENER_INCLUDED_HPP

#include <list>

#include "Button.hpp"

class WidgetListener
{
    public:
        WidgetListener();
        std::list<Button *>* getListeWidgets();
        virtual void action(int idWidgetClique) = 0;
        virtual void draw() = 0;
        virtual ~WidgetListener();
    protected:
        void addWidget(Button* button);
        void drawWidgets();
        void errorId(int id);
    private:
        std::list<Button *> listeButtons;
};

#endif // WIDGETLISTENER_INCLUDED_HPP
