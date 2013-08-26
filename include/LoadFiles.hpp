#ifndef LOADFILES_INCLUDED_HPP
#define LOADFILES_INCLUDED_HPP

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <string>

class LoadFiles
{
public:
    LoadFiles();
    sf::Font* getPoliceArial() const;
    sf::Texture* getImgBackgroundMenu() const;
    sf::Texture* getImgButton() const;
    sf::Texture* getImgButtonSurvol() const;
    sf::Texture* getImgButtonClic() const;
    sf::Texture* getSymboleAutomaticWeapon() const;
    sf::Texture* getSymboleShrapnelWeapon() const;
    sf::Texture* getSymboleLaserWeapon() const;
    sf::Texture* getImgCheckBox() const;
    sf::Texture* getImgCheckBoxClic() const;
    virtual ~LoadFiles();
protected:
private:
    sf::Font* policeArial;
    sf::Texture* imgBackgroundMenu;
    sf::Texture* imgButton;
    sf::Texture* imgButtonSurvol;
    sf::Texture* imgButtonClic;
    sf::Texture* symboleAutomaticWeapon;
    sf::Texture* symboleShrapnelWeapon;
    sf::Texture* symboleLaserWeapon;
    sf::Texture* imgCheckBox;
    sf::Texture* imgCheckBoxClic;

    std::string fichierIntrouvable;
};

#endif // LOADFILES_INCLUDED_HPP
