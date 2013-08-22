#ifndef IMAGEMANAGER_H_INCLUDED
#define IMAGEMANAGER_H_INCLUDED

#include <map>
#include <iostream>

#include <SFML/Graphics.hpp>

class image_manager
{
public:

	~image_manager();

	static const sf::Image&	get_image( const std::string& filename, sf::Color mask=sf::Color::Green);
	static void				delete_image( const sf::Image& image );
	static void				delete_image( const std::string& filename );
	static void				add_resource_directory( const std::string& directory );
	static void				remove_resource_directory( const std::string& directory );
private:
    image_manager();

	image_manager( const image_manager& );
	image_manager& operator =( const image_manager& );

	static std::map< std::string, sf::Image > images_;
	static std::vector< std::string > resource_directories_;
};

#endif // IMAGEMANAGER_H_INCLUDED
