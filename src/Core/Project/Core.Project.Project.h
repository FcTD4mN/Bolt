#pragma once


#include <SFML/Graphics.hpp>
#include <tinyxml2.h>
#include <set>

#include "Core.Base.FileSystem.h"

namespace nScreen { class cScreen; }


namespace nCore {
namespace nProject {


class cProject
{
public:
    ~cProject();
    cProject( const std::string& iProjectName, const std::string& iProjectFolder );
    cProject( const nStdFileSystem::path &iProjectFilePath );

public:
    void Initialize();
    void Finalize();

public:
    // Screen
    void AddScreen( ::nScreen::cScreen* iScreen );
    void SetCurrentScreen( const std::string& iScreenName );
    void LoadScreen( const std::string& iScreenName );
    void RemoveScreen( const std::string& iScreenName );
    ::nScreen::cScreen*     CurrentScreen();
    ::nScreen::cScreen*     GetScreenByName( const std::string& iScreenName );

public:
    // Access/Get
    int  ResolutionWidth() const;
    int  ResolutionHeight() const;
    int  LimitFramerate() const;

    void  SetResolution( int iWidth, int iHeight );
    void  SetLimitFramerate( int iFramerate );

    const std::string&              Name() const;
    void                            Name( const std::string& iNewName );
    nStdFileSystem::path            ProjectDirectory() const;
    const nStdFileSystem::path&     ProjectFilePath() const;
    void                            ProjectFilePath( const nStdFileSystem::path& iNewFilepath );

public:
    // EDITOR
    int                     ScreenCount();
    ::nScreen::cScreen*     ScreenAtIndex( int iIndex );
    void                    RemoveScreenAtIndex( int iIndex );
    int                     CurrentScreenIndex() const;
    void                    MakeProjectDirectories() const;

//public:
//    void Update( unsigned int iDeltaTime );
//    void Draw( sf::RenderTarget* iRenderTarget );

public:
    // Input/Output
    virtual  void SaveXML() const;
    virtual  void LoadXML();

protected:
    std::string                         mProjectName;
    nStdFileSystem::path                mProjectFilePath; //For now, this path has to be coherent with the project folder, if we don't want this, we'll have to store project main folder in the proj file
    std::vector< ::nScreen::cScreen* >  mScreens; // Set because we can only have a screen once
    int                                 mCurrentScreenIndex;

    int                                 mResolutionWidth;
    int                                 mResolutionHeight;
    int                                 mLimitFramerate;
};


} // namespace nProject
} // namespace nCore

