#pragma once

#include <SFML/Graphics.hpp>

namespace nGlobal {


class cGlobalProperties
{
private:
    ~cGlobalProperties();
    cGlobalProperties();

public:
    static cGlobalProperties * Instance();

public:
    void  SetProjectSize( const sf::Vector2f& iSize );
    void  SetProjectFolder( const std::string& iProjectFolder );
    void  SetTheMainWindow( sf::RenderWindow* iTheMainWindow );
public:
    const sf::Vector2f& GetProjectSize();
    const std::string&  GetProjectFolder();
	sf::RenderWindow*  GetTheMainWindow();

protected:
    sf::Vector2f		mProjectSize;
    std::string			mProjectFolder;
	sf::RenderWindow*	mTheMainWindow;
};


} // namespace nApplication

