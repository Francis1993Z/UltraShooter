#ifndef WIDGETMANAGER_INCLUDED_HPP
#define WIDGETMANAGER_INCLUDED_HPP

#include <SFML/Graphics.hpp>

#include <Button.hpp>

class WidgetManager
{
    public:
        WidgetManager();
        void updatePosSouris(sf::Vector2i posSouris);
        void setCurrentListeWidgets(std::vector<Button>& listeAdressesButton);
        void collisionSourisButton(float x, float y);
        virtual ~WidgetManager();
    protected:
    private:
        std::vector<Button>* listeButtons;
};

#endif // WIDGETMANAGER_INCLUDED_HPP
