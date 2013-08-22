#include "TextureManager.h"
#include "imagemanager.h"
/*
bool TextureManager::isAlreadyInstancied = false;
TextureManager* TextureManager::instance = 0;
*/
TextureManager::TextureManager()
{

}
/*
TextureManager* TextureManager::getInstance()
{
    if(!isAlreadyInstancied)
        {
           TextureManager::instance = new TextureManager();
            isAlreadyInstancied = true;
                image_manager::getInstance()->add_resource_directory(getCWD());
        }

    return instance;
}*/

map<string, sf::Texture*> TextureManager::textures;

sf::Texture *TextureManager::getTexture(string str)
{

   // See if we have already loaded this texture
   if(textures.find(str) != textures.end())
      return textures[str];

   // Haven't loaded it yet, time to create it
   sf::Texture *texture = new sf::Texture();

   if(texture->loadFromImage(image_manager::getInstance()->get_image(str)))
   {
      textures[str] = texture;
      return textures[str];
   }
   else
   {
      // Could not load the file
      delete texture;
      return NULL;
   }

}

TextureManager::~TextureManager()
{

   // Delete all of the textures we used
   sf::Texture *texture;
   map<string, sf::Texture*>::iterator iter = textures.begin();
   while(iter != textures.end())
   {
      texture = iter->second;
      delete texture;
      iter++;
   }

}
