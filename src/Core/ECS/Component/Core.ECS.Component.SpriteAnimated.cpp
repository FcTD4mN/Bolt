#include "Core.ECS.Component.SpriteAnimated.h"


#include "Core.Base.ResourceManager.h"


namespace nECS {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cSpriteAnimated::~cSpriteAnimated()
{
}


cSpriteAnimated::cSpriteAnimated() :
    tSuperClass( "spriteanimated" )
{
    Build( "empty", 1, 1 );
}


cSpriteAnimated::cSpriteAnimated( const std::string& iFile, int iW, int iH ) :
    tSuperClass( "spriteanimated" ),
    mCurrentSpriteRect( 0, 0, iW, iH )
{
    Build( iFile, iW, iH );
}


cSpriteAnimated::cSpriteAnimated( const cSpriteAnimated & iSpriteAnimated ) :
    tSuperClass( iSpriteAnimated ),
    mSpriteSheet( iSpriteAnimated.mSpriteSheet ), // Copy pointer -> Same object, but this is what we want, we don't copy a same texture ( that's why we have a resource manager )
    mSprite( iSpriteAnimated.mSprite ),
    mCurrentSpriteRect( iSpriteAnimated.mCurrentSpriteRect ),
    mClock( iSpriteAnimated.mClock ),
    mNumberOfSprites( iSpriteAnimated.mNumberOfSprites )
{
    BuildCallbacks();
}


void
cSpriteAnimated::Build( const std::string & iFile, int iW, int iH )
{
    AddNewVariable( "filename", ::nBase::cVariant::MakeVariant( iFile ) );
    AddNewVariable( "framerate", ::nBase::cVariant::MakeVariant( 24.0 ) );
    AddNewVariable( "paused", ::nBase::cVariant::MakeVariant( false ) );
    AddNewVariable( "flip", ::nBase::cVariant::MakeVariant( false ) );

    AddNewVariable( "currentframe", ::nBase::cVariant::MakeVariant( 1 ) );
    AddNewVariable( "spritewidth", ::nBase::cVariant::MakeVariant( iW ) );
    AddNewVariable( "spriteheight", ::nBase::cVariant::MakeVariant( iH ) );

    BuildCallbacks();

    mCurrentSpriteRect = sf::IntRect( 0, 0, iW, iH );

    if( iFile != "empty" )
    {
        SetSpriteSheet( iFile );
        UpdateTextureRect();
    }
}


void
cSpriteAnimated::BuildCallbacks()
{
    SetVarValueChangedCallback( "filename", [ this ](){

        SetSpriteSheet( GetVar( "filename" )->GetValueString() );
        UpdateTextureRect();

    } );

    SetVarValueChangedCallback( "flip", [ this ](){

        UpdateTextureRect();
    } );


    SetVarValueChangedCallback( "currentframe", [ this ](){

        auto varCurrentFrame = GetVar( "currentframe" );

        if( varCurrentFrame->GetValueNumber() < 1 )
            varCurrentFrame->SetValueNumber( 1 );
        else if( varCurrentFrame->GetValueNumber() > mNumberOfSprites )
            varCurrentFrame->SetValueNumber( mNumberOfSprites );

        UpdateTextureRect();

    } );


    SetVarValueChangedCallback( "spritewidth", [ this ](){

        UpdateTextureRect();
    } );


    SetVarValueChangedCallback( "spriteheight", [ this ](){

        UpdateTextureRect();
    } );

}


void
cSpriteAnimated::UpdateTextureRect()
{
    int spriteWidth = int(GetVar( "spritewidth" )->GetValueNumber());
    mCurrentSpriteRect.left = (int(GetVar( "currentframe" )->GetValueNumber() )- 1) * spriteWidth;
    mCurrentSpriteRect.width = spriteWidth;
    if( Flip() )
    {
        mCurrentSpriteRect.left += spriteWidth;
        mCurrentSpriteRect.width = spriteWidth * -1;
    }

    mSprite.setTextureRect( mCurrentSpriteRect );
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------- Copy
// -------------------------------------------------------------------------------------


cComponent*
cSpriteAnimated::Clone()
{
    return  new cSpriteAnimated( *this );
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Access
// -------------------------------------------------------------------------------------


const std::string&
cSpriteAnimated::FileName()
{
    return  GetVar( "filename" )->GetValueString();
}


double
cSpriteAnimated::Framerate()
{
    return  GetVar( "framerate" )->GetValueNumber();
}


bool
cSpriteAnimated::Paused()
{
    return  GetVar( "paused" )->GetValueBool();
}


void
cSpriteAnimated::FileName( const std::string & iValue )
{
    GetVar( "filename" )->SetValueString( iValue );
}


void
cSpriteAnimated::Framerate( double iValue )
{
    GetVar( "framerate" )->SetValueNumber( iValue );
}


void
cSpriteAnimated::Paused( bool iValue )
{
    GetVar( "paused" )->SetValueBool( iValue );
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------- Handle functions
// -------------------------------------------------------------------------------------


void
cSpriteAnimated::NextFrame()
{
    auto varCurrentFrame = GetVar( "currentframe" );
    varCurrentFrame->SetValueNumber( ( int( varCurrentFrame->GetValueNumber()) % mNumberOfSprites ) + 1 );

    UpdateTextureRect();
}


void
cSpriteAnimated::PreviousFrame()
{
    auto varCurrentFrame = GetVar( "currentframe" );
    varCurrentFrame->SetValueNumber( varCurrentFrame->GetValueNumber() - 1 );
    if( varCurrentFrame->GetValueNumber() < 1 )
        varCurrentFrame->SetValueNumber( mNumberOfSprites );

    UpdateTextureRect();
}


bool
cSpriteAnimated::Flip()
{
    return  GetVar( "flip" )->GetValueBool();
}


void cSpriteAnimated::Flip( bool iFlip )
{
    GetVar( "flip" )->SetValueBool( iFlip );
}


void
cSpriteAnimated::SetSpriteSheet( const std::string & iFile )
{
    mSpriteSheet = ::nBase::cResourceManager::Instance()->GetTexture( iFile );
    mSprite.setTexture( *mSpriteSheet );

    mSprite.setOrigin( sf::Vector2f( float( mCurrentSpriteRect.width / 2 ), float( mCurrentSpriteRect.height / 2 ) ) );

    mNumberOfSprites = mSpriteSheet->getSize().x / mCurrentSpriteRect.width;
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Input/Output
// -------------------------------------------------------------------------------------


void
cSpriteAnimated::SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument )
{
    tSuperClass::SaveXML( iNode, iDocument );
}


void
cSpriteAnimated::LoadXML( tinyxml2::XMLElement* iNode )
{
    tSuperClass::LoadXML( iNode );

    mCurrentSpriteRect.width =  int(GetVar( "spritewidth" )->GetValueNumber());
    mCurrentSpriteRect.height = int(GetVar( "spriteheight" )->GetValueNumber());

    SetSpriteSheet( FileName() );
    UpdateTextureRect();
}


} // namespace nECS

