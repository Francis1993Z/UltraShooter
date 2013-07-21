#ifndef WIDGETLISTENER_INCLUDED_HPP
#define WIDGETLISTENER_INCLUDED_HPP

#include <list>

#include "Button.hpp"

class WidgetListener
{
    public:
        WidgetListener();
        void addWidget(Button button);
        void drawWidgets();
        virtual ~WidgetListener();
    protected:
    private:
        bool ajouter;
        std::list<Button> listeButtons;
};

#endif // WIDGETLISTENER_INCLUDED_HPP
