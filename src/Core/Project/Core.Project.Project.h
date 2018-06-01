#pragma once

#include <SFML/Graphics.hpp>
#include <tinyxml2.h>

namespace nScreen { class cScreen; }

namespace nProject {

class cProject
{
public:
    cProject( const std::string& iProjectName, const std::string& iProjectFolder );

public:
    void Initialize();
    void Finalize();

public:
    // Screen
    void PushScreen( ::nScreen::cScreen* iScreen );
    void PopScreen();
    ::nScreen::cScreen*  CurrentScreen();

public:
    // Access/Get
    int  ResolutionWidth() const;
    int  ResolutionHeight() const;
    int  LimitFramerate() const;

    void  SetResolution( int iWidth, int iHeight );
    void  SetLimitFramerate( int iFramerate );

//public:
//    void Update( unsigned int iDeltaTime );
//    void Draw( sf::RenderTarget* iRenderTarget );

public:
    // Input/Output
    virtual  void SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument );
    virtual  void LoadXML();

protected:
    std::string                         mProjectName;
    std::string                         mProjectFolder;
    std::vector< ::nScreen::cScreen* >  mScreenStack;

    int                                 mResolutionWidth;
    int                                 mResolutionHeight;
    int                                 mLimitFramerate;
};


} // namespace nApplication

