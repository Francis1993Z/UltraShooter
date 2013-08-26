#include "LoadFiles.hpp"

#include <iostream>

using namespace std;
using namespace sf;

LoadFiles::LoadFiles()
{
    fichierIntrouvable = "";
    policeArial = new Font();
    imgBackgroundMenu = new Texture();
    imgButton = new Texture();
    imgButtonSurvol = new Texture();
    imgButtonClic = new Texture();
    symboleAutomaticWeapon = new Texture();
    symboleShrapnelWeapon = new Texture();
    symboleLaserWeapon = new Texture();
    imgCheckBox = new Texture();
    imgCheckBoxClic = new Texture();

    if (!policeArial->loadFromFile("ressources/fonts/arial.ttf"))
        {

            fichierIntrouvable = "arial.ttf";
        }
    else if(!imgBackgroundMenu->loadFromFile("ressources/backgrounds/menu.png"))
        {

            fichierIntrouvable = "menu.png";
        }
    else if(!imgButton->loadFromFile("ressources/widgets/button.png"))
        {

            fichierIntrouvable = "button.png";
        }
    else if(!imgButtonSurvol->loadFromFile("ressources/widgets/buttonSurvol.png"))
        {

            fichierIntrouvable = "buttonSurvol.png";
        }
    else if(!imgButtonClic->loadFromFile("ressources/widgets/buttonClic.png"))
        {

            fichierIntrouvable = "buttonClic.png";
        }
    else if(!symboleAutomaticWeapon->loadFromFile("ressources/symboles/AutomaticWeapon.png"))
        {

            fichierIntrouvable = "AutomaticWeapon.png";
        }
    else if(!symboleShrapnelWeapon->loadFromFile("ressources/symboles/ShrapnelWeapon.png"))
        {

            fichierIntrouvable = "ShrapnelWeapon.png";
        }
    else if(!imgCheckBox->loadFromFile("ressources/widgets/checkBox.png"))
        {

            fichierIntrouvable = "checkBox.png";
        }
    else if(!imgCheckBoxClic->loadFromFile("ressources/widgets/checkBoxClic.png"))
        {

            fichierIntrouvable = "checkBoxClic.png";
        }


    if(fichierIntrouvable != "")
        {

            cerr<<"ERROR : Can't load "+fichierIntrouvable+" in LoadFiles.cpp"<<endl;
            exit(15);
        }
}

Font* LoadFiles::getPoliceArial() const
{

    return policeArial;
}

Texture* LoadFiles::getImgBackgroundMenu() const
{

    return imgBackgroundMenu;
}

Texture* LoadFiles::getImgButton() const
{

    return imgButton;
}

Texture* LoadFiles::getImgButtonSurvol() const
{

    return imgButtonSurvol;
}

Texture* LoadFiles::getImgButtonClic() const
{

    return imgButtonClic;
}

Texture* LoadFiles::getSymboleAutomaticWeapon() const{

    return symboleAutomaticWeapon;
}

Texture* LoadFiles::getSymboleShrapnelWeapon() const{

    return symboleShrapnelWeapon;
}

Texture* LoadFiles::getSymboleLaserWeapon() const{

    return symboleLaserWeapon;
}

Texture* LoadFiles::getImgCheckBox() const
{

    return imgCheckBox;
}

Texture* LoadFiles::getImgCheckBoxClic() const
{

    return imgCheckBoxClic;
}

LoadFiles::~LoadFiles()
{
    delete policeArial;
    delete imgBackgroundMenu;
    delete imgButton;
    delete imgButtonSurvol;
    delete imgButtonClic;
    delete symboleAutomaticWeapon;
    delete symboleShrapnelWeapon;
    delete symboleLaserWeapon;
    delete imgCheckBox;
    delete imgCheckBoxClic;
}
