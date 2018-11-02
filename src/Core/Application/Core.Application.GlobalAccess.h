#pragma once


#include <SFML/Graphics.hpp>

#define  PROJECTSIZE    ::nCore::nApplication::cGlobalAccess::Instance()->ProjectSize()
#define  PROJECTDIR     ::nCore::nApplication::cGlobalAccess::Instance()->ProjectFolder()
#define  MAINWIN        ::nCore::nApplication::cGlobalAccess::Instance()->TheMainWindow()


namespace nCore {
namespace nApplication {


class cGlobalAccess
{
private:
    ~cGlobalAccess();
    cGlobalAccess();

public:
    static  cGlobalAccess*  Instance();

public:
    void  ProjectSize( const  sf::Vector2f&  iSize );
    void  ProjectFolder( const  std::string&  iProjectFolder );
    void  TheMainWindow( sf::RenderWindow*  iTheMainWindow );
public:
    const  sf::Vector2f&    ProjectSize();
    const  std::string&     ProjectFolder();
    sf::RenderWindow*       TheMainWindow();

protected:
    sf::Vector2f        mProjectSize;
    std::string         mProjectFolder;
    sf::RenderWindow*   mTheMainWindow;
};


} // namespace nApplication
} // namespace nCore

