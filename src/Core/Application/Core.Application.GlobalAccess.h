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
public:
    const sf::Vector2f& GetProjectSize();
    const std::string&  GetProjectFolder();

protected:
    sf::Vector2f    mProjectSize;
    std::string     mProjectFolder;
};


} // namespace nApplication

