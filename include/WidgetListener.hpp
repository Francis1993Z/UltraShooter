#ifndef WIDGETLISTENER_INCLUDED_HPP
#define WIDGETLISTENER_INCLUDED_HPP

#include "Button.hpp"

class WidgetListener
{
    public:
        WidgetListener();
        void addWidget(Button button);
        void drawWidgets(sf::RenderWindow& game);
        virtual ~WidgetListener();
    protected:
    private:
        bool ajouter;
        std::vector<Button> listeButtons;
};

#endif // WIDGETLISTENER_INCLUDED_HPP
