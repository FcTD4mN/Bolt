#include "SightSystem.h"

#include "Math/Utils.h"
#include "Math/Ray.h"

#include "ECS/Core/Entity.h"
#include "ECS/Utilities/EntityParser.h"
#include "ECS/Core/World.h"

#include "GameMockup/GameApplication.h"
#include "GameMockup/Components/FieldOfView.h"
#include "GameMockup/Components/Position.h"
#include "GameMockup/Components/Size.h"
#include "GameMockup/Components/Direction.h"

#include "Mapping/PhysicEntityGrid.h"

#include "SFML/Graphics.hpp"

#include <iostream>


#define FOVSplitThreshold 1

// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cSightSystem::~cSightSystem()
{
}


cSightSystem::cSightSystem() :
    tSuperClass()
{
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------- Init/Finalize
// -------------------------------------------------------------------------------------


void
cSightSystem::Initialize()
{
}


void
cSightSystem::Finalize()
{
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------- Update/Draw
// -------------------------------------------------------------------------------------


void
cSightSystem::Draw( sf::RenderTarget* iRenderTarget )
{
    for( auto fov : mFOVDrawer )
    {
        for( int i = 0; i < fov.size(); ++i )
        {
            for( int j = 0; j < fov[ i ].getVertexCount(); ++j )
            {
                fov[ i ].setPrimitiveType( sf::Triangles );
                fov[ i ][ j ].color = sf::Color( 200,20,20,50 );
            }
            iRenderTarget->draw( fov[ i ] );
        }
    }
}

void Oui( std::vector< int >* oSubTrianglesOutput )
{
    //oSubTrianglesOutput->clear();
    oSubTrianglesOutput->push_back( 5 );
}

void
cSightSystem::Update( unsigned int iDeltaTime )
{
    cEntityGrid* entityMap = cGameApplication::App()->EntityMap();

    mFOVDrawer.clear();
    unsigned int cpus = std::thread::hardware_concurrency();

    for( int i = 0; i < mWatchers.size(); ++i )
    {
        cEntity* entity = mWatchers[ i ];

        //mTransformationAngleSort = mTransformationAngleSort.Identity;
        mTriangles.clear();

        auto position = dynamic_cast< cPosition* >( entity->GetComponentByName( "position" ) );
        auto size = dynamic_cast< cSize* >( entity->GetComponentByName( "size" ) );
        auto direction = dynamic_cast< cDirection* >( entity->GetComponentByName( "direction" ) );
        auto fieldofview = dynamic_cast< cFieldOfView* >( entity->GetComponentByName( "fieldofview" ) );

        // This is the transformation that allows to go in the watcher's referential
        //mTransformationAngleSort.rotate( float( RadToDeg( GetAngleBetweenVectors( gXAxisVector, direction->mDirection ) ) ) );
        //mTransformationAngleSort.translate( -position->mPosition );
        sf::VertexArray subFov;

        // Important points of main FOV
        sf::Vector2f fovOrigin;
        sf::Vector2f fovB;

        // Get FOV triangles
        fovOrigin = position->mPosition; // Base point of the triangle
        float semiAngle = float(fieldofview->mAngle / 2.0F);
        sf::Transform rotation;
        rotation.rotate( semiAngle );

        // This vector is the vector of the bisectrice of the FOV
        sf::Vector2f baseVector = direction->mDirection * float(fieldofview->mDistance);
        fovB = rotation.transformPoint( baseVector ); // This will be the most top left point of the first triangle
        // Reset the rotation
        rotation = rotation.Identity;
        // Set it to FOV angle / number of split, negative so it goes right and not left
        rotation.rotate( float( -fieldofview->mAngle ) / FOVSplitThreshold );

        for( int i = 0; i < FOVSplitThreshold; ++i )
        {
            // We start a new triangle, that has ptA and ptB from the previous
            subFov.clear();
            subFov.append( fovOrigin );
            subFov.append( fovOrigin + fovB );
            // And for each split, we apply the rotation to the top left point, creating the top right point
            // for the Nth triangle
            fovB = rotation.transformPoint( fovB );
            subFov.append( fovB + fovOrigin );
            mTriangles.push_back( subFov );
        }

        mFOVBBox = GetTriangleSetBBox( mTriangles );

        std::vector< cEntity* > entitiesInFOVBBox;
        entityMap->GetEntitiesInBoundingBox( &entitiesInFOVBBox, mFOVBBox );

        for( auto v : entitiesInFOVBBox )
        {
            // We don't analyse the watcher itself
            if( v == entity )
                continue;

            auto positionENT = dynamic_cast< cPosition* >( v->GetComponentByName( "position" ) );
            auto sizeENT = dynamic_cast< cSize* >( v->GetComponentByName( "size" ) );

            sf::VertexArray analysisVisibleBox( sf::Points, 4 );
            analysisVisibleBox[ 0 ] = positionENT->mPosition;
            analysisVisibleBox[ 1 ] = positionENT->mPosition + sf::Vector2f( 0.0F, sizeENT->mSize.y );
            analysisVisibleBox[ 2 ] = positionENT->mPosition + sizeENT->mSize;
            analysisVisibleBox[ 3 ] = positionENT->mPosition + sf::Vector2f( sizeENT->mSize.x, 0.0F );

            mThread.reserve( mTriangles.size() );
            std::vector< std::vector< sf::VertexArray >* > subTriangles;

            for( int i = 0; i < mTriangles.size(); ++i )
            {
                std::vector< sf::VertexArray >* gogo = new std::vector< sf::VertexArray >();
                subTriangles.push_back( gogo );

                //mThread.push_back( std::thread( &TriangleSubDivisionUsingPolygonMultiThreadCall, gogo, &mTriangles[ i ], &analysisVisibleBox ) );
                TriangleSubDivisionUsingPolygon( gogo, mTriangles[ i ], analysisVisibleBox );
            }



            //std::vector< std::vector< sf::VertexArray > > vec;
            //for( int i = 0; i < 2; ++i )
            //{
            //    //vec.push_back( std::vector< sf::VertexArray >() );
            //    //std::vector< sf::VertexArray >* vector = &vec[ vec.size() - 1 ];

            //    std::vector< int >* merde = new std::vector< int >;
            //    merde->push_back( 1 );
            //    merde->push_back( 2 );
            //    mThread.push_back( std::thread( &Oui, merde ) );
            //}

            for( int i = 0; i < mThread.size(); ++i )
            {
                mThread[ i ].join();
            }

            if( subTriangles.size() > 0 )
            {
                mTriangles.clear();
                for( auto sub : subTriangles )
                {
                    for( int i = 0; i < sub->size(); ++i )
                    {
                        mTriangles.push_back( (*sub)[ i ] );
                    }

                }
            }
            subTriangles.clear();
            mThread.clear();

        }// for all entities

        mFOVDrawer.push_back( mTriangles );
    }
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Entity
// -------------------------------------------------------------------------------------


void
cSightSystem::IncomingEntity( cEntity* iEntity )
{
    auto position       = iEntity->GetComponentByName( "position" );
    auto size           = iEntity->GetComponentByName( "size" );
    auto direction      = iEntity->GetComponentByName( "direction" );
    auto fieldofview    = iEntity->GetComponentByName( "fieldofview" );

    if( iEntity->HasTag( "hero" ) )
        mPointsOfInterest.push_back( iEntity );
    else if( position && size && direction && fieldofview )
        mWatchers.push_back( iEntity );

    AcceptEntity( iEntity );
}


void
cSightSystem::EntityLost( cEntity * iEntity )
{
    auto position = iEntity->GetComponentByName( "position" );
    auto size = iEntity->GetComponentByName( "size" );
    auto direction = iEntity->GetComponentByName( "direction" );
    auto fieldofview = iEntity->GetComponentByName( "fieldofview" );

    if( iEntity->HasTag( "hero" ) )
    {
        for( int i = 0; i < mPointsOfInterest.size(); ++i )
        {
            if( iEntity == mPointsOfInterest[ i ] )
                mPointsOfInterest.erase( mPointsOfInterest.begin() + i );
        }
    }
    else if( position && size && direction && fieldofview )
    {
        for( int i = 0; i < mWatchers.size(); ++i )
        {
            if( iEntity == mWatchers[ i ] )
                mWatchers.erase( mWatchers.begin() + i );
        }
    }

    tSuperClass::EntityLost( iEntity );
}



