#include "imagemanager.h"
#include "GlobalFunctions.h"

	std::map< std::string, sf::Image > image_manager::images_;
	std::vector< std::string > image_manager::resource_directories_;
image_manager::image_manager()
{
}

image_manager::~image_manager()
{
	images_.clear();
	resource_directories_.clear();
}




const sf::Image& image_manager::get_image( const std::string& filename, sf::Color mask )
{
	// Check, whether the image already exists
	for( std::map<std::string, sf::Image>::const_iterator it = images_.begin();
		 it != images_.end();
		 ++it)
	{
		if( filename == it->first )
		{
			std::cout << "DEBUG_MESSAGE: " << filename << " using existing image.\n";
			return it->second;
		}
	}

	// The image doesen't exists. Create it and save it.
	sf::Image image;

	// Search project's main directory
	if( image.loadFromFile( filename ) )
	{
	    image.createMaskFromColor(mask);
		images_[filename] = image;
		std::cout << "DEBUG_MESSAGE: " << filename << " loading image.\n";
		return images_[filename];
	}

	// If the image has still not been found, search all registered directories
	for( std::vector< std::string >::iterator it = resource_directories_.begin();
		 it != resource_directories_.end();
		 ++it )
	{
		if( image.loadFromFile( (*it) + filename ) )
		{
            image.createMaskFromColor(sf::Color(0,255,0));
			images_[filename] = image;
			std::cout << "DEBUG_MESSAGE: " << filename << " loading image.\n";
			return images_[filename];
		}

	}

	std::cout << "GAME_ERROR: Image was not found. It is filled with an empty image.\n";
	images_[filename] = image;
	return images_[filename];
}

void image_manager::delete_image( const sf::Image& image )
{
	for( std::map<std::string, sf::Image>::iterator it = images_.begin();
		 it != images_.end();
		 ++it)
	{
		if( &image == &it->second )
		{
			images_.erase(it);
                        return;
		}
	}
}

void image_manager::delete_image( const std::string& filename )
{
	std::map<std::string, sf::Image>::iterator it = images_.find( filename );
	if( it != images_.end() )
		images_.erase(it);
}

void image_manager::add_resource_directory( const std::string& directory )
{
	// Check whether the path already exists
	for( std::vector<std::string>::const_iterator it  = resource_directories_.begin();
		 it != resource_directories_.end();
		++it )
	{
		// The path exists. So it isn't necessary to add id once more.
		if( directory == (*it) )
			return;
	}

	// insert the directory
	resource_directories_.push_back( directory );
}

void image_manager::remove_resource_directory( const std::string& directory )
{
	for( std::vector<std::string>::iterator it  = resource_directories_.begin();
		 it != resource_directories_.end(); )
	{
		// The path exists. So it isn't necessary to add id once more.
		if( directory == (*it) )
			it = resource_directories_.erase( it );
		else
			++it;
	}
}
