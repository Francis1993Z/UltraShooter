#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

using namespace std;

class TextureManager
{
   // The textures that are loaded
   static map<string, sf::Texture*> textures;

       // Constructor that is not used
   TextureManager();
public:

    //static TextureManager* getInstance();
   // Destructor which deletes the textures previously loaded
   ~TextureManager();
       //static bool isAlreadyInstancied; // Permet de savoir si une instance de TextureManager existe déjà ou non.
    //static TextureManager* instance; // Permet de retenir l'adresse de l'instance de TextureManager qui a été crée.

   // Loads the texture and returns a pointer to it
   // If it is already loaded, this function just returns it
   // If it cannot find the file, returns NULL
   static sf::Texture *getTexture(string str);
};

#endif
