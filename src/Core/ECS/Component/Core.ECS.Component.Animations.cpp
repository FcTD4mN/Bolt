#include "Core.ECS.Component.Animations.h"

#include "Core.Animation.Animation.h"


namespace nCore {
namespace nECS {
namespace nComponent {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cAnimations::~cAnimations()
{
    for( auto animation : mAnimations )
        delete  animation;

    mAnimations.clear();
}


cAnimations::cAnimations() :
    tSuperClass( "animations" ),
    mCurrentAnimation( 0 )
{
}


cAnimations::cAnimations( const cAnimations & iRHS ) :
    tSuperClass( iRHS )
{
    for( auto animation : iRHS.mAnimations )
        mAnimations.push_back( animation->Clone() );

    mCurrentAnimation = 0;
    if( mAnimations.size() > 0 )
        mCurrentAnimation = mAnimations[ 0 ];
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------- Copy
// -------------------------------------------------------------------------------------


::nCore::nECS::nCore::cComponent*
cAnimations::Clone() const
{
    return  new cAnimations(*this);
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------- Update/Draw
// -------------------------------------------------------------------------------------


void
cAnimations::Update( unsigned int iDeltaTime )
{
    mCurrentAnimation->Update( iDeltaTime );
}


void
cAnimations::Draw( sf::RenderTarget * iRenderTarget )
{
    mCurrentAnimation->Draw( iRenderTarget );
}


// -------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------- Set/Gets
// -------------------------------------------------------------------------------------


::nCore::nAnimation::cAnimation*
cAnimations::AddSpriteSheetBasedAnimation( const std::string & iAnimationName, const nStdFileSystem::path & iFullFilePath, int iNumberOfImagesX, int iNumberOfImagesY )
{
    auto newAnimation = new ::nCore::nAnimation::cAnimation( iAnimationName );
    newAnimation->AddSpriteSheet( iFullFilePath, iNumberOfImagesX, iNumberOfImagesY );
    mAnimations.push_back( newAnimation );
    if( mCurrentAnimation == 0 )
        mCurrentAnimation = newAnimation;

    return  newAnimation;
}


::nCore::nAnimation::cAnimation*
cAnimations::AddMultiFilesBasedAnimation( const std::string & iAnimationName )
{
    auto newAnimation = new ::nCore::nAnimation::cAnimation( iAnimationName );
    mAnimations.push_back( newAnimation );
    if( mCurrentAnimation == 0 )
        mCurrentAnimation = newAnimation;

    return  newAnimation;
}


void
cAnimations::CurrentAnimation( const std::string & iAnimationName )
{
    auto animation = _AnimationByName( iAnimationName );
    if( animation )
        mCurrentAnimation = animation;
}


std::string
cAnimations::CurrentAnimation() const
{
    for( auto animation : mAnimations )
        if( animation == mCurrentAnimation )
            return  animation->Name();

    return  "";
}


void
cAnimations::CurrentAnimationCurrentFrame( int iCurrentFrame )
{
    mCurrentAnimation->CurrentFrame( iCurrentFrame );
}


int
cAnimations::CurrentAnimationCurrentFrame() const
{
    return  mCurrentAnimation->CurrentFrame();
}


void
cAnimations::CurrentAnimationFrameRate( float iFrameRate )
{
    mCurrentAnimation->FrameRate( iFrameRate );
}


float
cAnimations::CurrentAnimationFrameRate() const
{
    return 0.0f;
}


void
cAnimations::CurrentAnimationNextFrame()
{
    mCurrentAnimation->NextFrame();
}


void
cAnimations::CurrentAnimationPrevFrame()
{
    mCurrentAnimation->PreviousFrame();
}


int
cAnimations::CurrentAnimationSpriteWidth() const
{
    return  mCurrentAnimation->SpriteWidth();
}


int
cAnimations::CurrentAnimationSpriteHeight() const
{
    return  mCurrentAnimation->SpriteHeight();
}


void
cAnimations::CurrentAnimationSpritePosition( const sf::Vector2f & iPosition )
{
    mCurrentAnimation->SpritePosition( iPosition );
}


void
cAnimations::CurrentAnimationSpriteOrigin( const sf::Vector2f & iOrigin )
{
    mCurrentAnimation->SpriteOrigin( iOrigin );
}


void
cAnimations::CurrentAnimationSpriteScale( const sf::Vector2f & iScale )
{
    mCurrentAnimation->SpriteScale( iScale );
}


void
cAnimations::CurrentAnimationIsFlipped( bool iFlipped )
{
    mCurrentAnimation->Flipped( iFlipped );
}


bool
cAnimations::CurrentAnimationIsFlipped() const
{
    return  mCurrentAnimation->Flipped();
}


void
cAnimations::CurrentAnimationIsPaused( bool iPaused )
{
    mCurrentAnimation->Paused( iPaused );
}


bool
cAnimations::CurrentAnimationIsPaused() const
{
    return  mCurrentAnimation->Paused();
}


void
cAnimations::CurrentAnimationPlay()
{
    mCurrentAnimation->Play();
}


void
cAnimations::SaveXML( tinyxml2::XMLElement * iNode, tinyxml2::XMLDocument * iDocument ) const
{
    tSuperClass::SaveXML( iNode, iDocument );

    tinyxml2::XMLElement* animationsNode = iDocument->NewElement( "animations" );
    for( auto animation : mAnimations )
    {
        tinyxml2::XMLElement* animationNode = iDocument->NewElement( "animation" );
        animationNode->SetAttribute( "name", animation->Name().c_str() );
        animation->SaveXML( animationNode, iDocument );
        animationsNode->LinkEndChild( animationNode );
    }

    iNode->LinkEndChild( animationsNode );
}

void
cAnimations::LoadXML( tinyxml2::XMLElement * iNode )
{
    tSuperClass::LoadXML( iNode );

    tinyxml2::XMLElement* animationsNode = iNode->FirstChildElement( "animations" );
    for( tinyxml2::XMLElement* animation = animationsNode->FirstChildElement( "animation" ); animation; animation = animation->NextSiblingElement() )
    {
        std::string animationName = animation->Attribute( "name" );
        auto newAnimation = AddEmptyAnimationAtIndex( animationName, int(mAnimations.size() - 1) );
        newAnimation->LoadXML( animation );
    }
}


::nCore::nAnimation::cAnimation*
cAnimations::_AnimationByName( const std::string & iName )
{
    for( auto animation : mAnimations )
        if( animation->Name() == iName )
            return  animation;

    return  nullptr;
}


void
cAnimations::SetAnimationNameAtIndex( const std::string& iName, int iIndex )
{
    mAnimations[ iIndex ]->Name( iName );
}


int
cAnimations::AnimationCount() const
{
    return  (int)mAnimations.size();
}


::nCore::nAnimation::cAnimation*
cAnimations::AnimationAtIndex( int iIndex )
{
    return  mAnimations[ iIndex ];
}


::nCore::nAnimation::cAnimation*
cAnimations::AddEmptyAnimationAtIndex( const std::string & iAnimationName, int iIndex )
{
    auto newAnimation = new ::nCore::nAnimation::cAnimation( iAnimationName );

    if( iIndex < 0 )
        mAnimations.push_back( newAnimation );
    else
        mAnimations.insert( mAnimations.begin() + iIndex, newAnimation );

    if( mCurrentAnimation == 0 )
        mCurrentAnimation = newAnimation;

    return  newAnimation;
}


void
cAnimations::RemoveAnimationAtIndex( int iIndex )
{
    delete  mAnimations[ iIndex ];
    mAnimations.erase( mAnimations.begin() + iIndex );
}


} // namespace nComponent
} // namespace nECS
} // namespace nCore

