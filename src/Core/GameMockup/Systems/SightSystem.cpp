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
    mInterestingHitPoints.setPrimitiveType( sf::Points );
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
    cEntityGrid* entityMap = cGameApplication::App()->EntityMap();

    // BBOx of fov
    //sf::RectangleShape bbox( sf::Vector2f( mFOVBBox.width, mFOVBBox.height ) );
    //bbox.setPosition( sf::Vector2f( mFOVBBox.left, mFOVBBox.top ) );
    //iRenderTarget->draw( bbox );

    for( int i = 0; i < mTriangles.size(); ++i )
    {
        mTriangles[ i ].setPrimitiveType( sf::Triangles );
        for( int j = 0; j < mTriangles[ i ].getVertexCount(); ++j )
        {
            mTriangles[ i ][ j ].color = sf::Color( i*20, i*10, 0, 100 );
        }

        iRenderTarget->draw( mTriangles[ i ] );
    }

    //for( int i = 0; i < mDEBUGClips.size(); ++i )
    //{
    //    mDEBUGClips[ i ].setPrimitiveType( sf::TriangleFan );
    //    for( int j = 0; j < mDEBUGClips[ i ].getVertexCount(); ++j )
    //    {
    //        mDEBUGClips[ i ][ j ].color = sf::Color( 255, 150, 0, 255 );
    //    }

    //    iRenderTarget->draw( mDEBUGClips[ i ] );
    //}

    //for( int i = 0; i < mDEBUGRays.size(); ++i )
    //{
    //    sf::VertexArray line( sf::Lines, 2 );
    //    line[ 0 ].position = mDEBUGRays[ i ].mPoint;
    //    line[ 0 ].color = sf::Color( i*50, 0, 0 );
    //    line[ 1 ].position = mDEBUGRays[ i ].mPoint + mDEBUGRays[ i ].mDirection;
    //    line[ 1 ].color = sf::Color( i*50, 0, 0 );
    //    iRenderTarget->draw( line );
    //}

    //if( mTriangles.size() > 0 )
    //{
    //    sf::VertexArray fovTrans = mTriangles[ 0 ];
    //    TransformPolygonUsingTransformation( &fovTrans, mTransformationAngleSort );
    //    iRenderTarget->draw( fovTrans );

    //    for( auto ent : mDEBUGEntities )
    //    {
    //        sf::VertexArray trans = ent;
    //        TransformPolygonUsingTransformation( &trans, mTransformationAngleSort );
    //        trans.setPrimitiveType( sf::Quads );
    //        iRenderTarget->draw( trans );
    //    }
    //}

    iRenderTarget->draw( mDEBUGHitPoints );

    for( int i = 0; i < mResultingSubTriangles.size(); ++i )
    {
        for( int j = 0; j < mResultingSubTriangles[ i ].getVertexCount(); ++j )
        {
            mResultingSubTriangles[ i ].setPrimitiveType( sf::Triangles );
            mResultingSubTriangles[ i ][ j ].color = sf::Color( (50*i)%255, ( 100 * i ) % 255, ( 10 * i ) % 255, 255 );
        }
        iRenderTarget->draw( mResultingSubTriangles[ i ] );
    }
    iRenderTarget->draw( mInterestingHitPoints );
}


void
cSightSystem::Update( unsigned int iDeltaTime )
{
    cEntityGrid* entityMap = cGameApplication::App()->EntityMap();

    mTransformationAngleSort = mTransformationAngleSort.Identity;
    mTriangles.clear();
    mResultingSubTriangles.clear();
    mDEBUGClips.clear();
    mDEBUGEntities.clear();
    mDEBUGRays.clear();
    mDEBUGHitPoints.clear();

    sf::Vector2f fovOrigin;
    sf::Vector2f fovB;

    for( int i = 0; i < mEntityGroup.size(); ++i )
    {
        cEntity* entity = mEntityGroup[ i ];

        auto position = dynamic_cast< cPosition* >( entity->GetComponentByName( "position" ) );
        auto size = dynamic_cast< cSize* >( entity->GetComponentByName( "size" ) );
        auto direction = dynamic_cast< cDirection* >( entity->GetComponentByName( "direction" ) );
        auto fieldofview = dynamic_cast< cFieldOfView* >( entity->GetComponentByName( "fieldofview" ) );

        // This is the transformation that allows to go in the watcher's referential
        mTransformationAngleSort.rotate( float( RadToDeg( GetAngleBetweenVectors( gXAxisVector, direction->mDirection ) ) ) );
        mTransformationAngleSort.translate( -position->mPosition );
        sf::VertexArray subFov;

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

        //for( auto v : entitiesInFOVBBox )
        for( auto v : mPointsOfInterest )
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
            mDEBUGEntities.push_back( analysisVisibleBox );

            // For each triangle in the set, we split it according to object in the fov
            for( int i = int(mTriangles.size() - 1); i >= 0; --i )
            {
                sf::VertexArray clipedPol = ClipPolygonPolygon( analysisVisibleBox, mTriangles[ i ] );
                // If this part of the fov doesn't clip with the polygon, we keep the whoe triangle, and we continue
                if( clipedPol.getVertexCount() == 0 )
                {
                    mResultingSubTriangles.push_back( mTriangles[ i ] );
                    continue;
                }

                // Situation : we have a unique hitpoint that is exactly on a vertex -> we add the fov intersection in interesting points.
                // BUT, sometimes, both points are the same. We then don't want to do the swap 1<->2 below.
                // This is to check that
                bool vertexIntersectionAndFovInterAreIdentical = false;
                sf::Vector2f idPoint( 0.0f, 0.0F ); // This is the point that is identical

                mDEBUGClips.push_back( clipedPol );
                std::vector< cRay > rayList;
                mInterestingHitPoints.clear();

                // Now we have the clipped polygon, we want to cast rays towards every vertexes to see
                // which part of the FOV is obstructed

                // =============================================================
                // =============================================================

                // The first ray we add is the left part of the sub fov
                cRay fovRightEdge( cEdgeF::MakePointPoint( mTriangles[ i ][ 0 ].position, mTriangles[ i ][ 2 ].position ), cRay::eRayType::kFovSide );
                rayList.push_back( fovRightEdge );
                mDEBUGRays.push_back( fovRightEdge.mRay );

                // Then finally the last ray is the right part of the sub fov
                cRay fovLeftEdge( cEdgeF::MakePointPoint( mTriangles[ i ][ 0 ].position, mTriangles[ i ][ 1 ].position ), cRay::eRayType::kFovSide );
                if( AddElementToVectorUnique( fovLeftEdge, &rayList ) )
                    mDEBUGRays.push_back( fovLeftEdge.mRay );

                // Then, one ray per vertex of the polygon
                for( int j = 0; j < clipedPol.getVertexCount(); ++j )
                {
                    // First we get for each vertex, the ray from fov's origin
                    // Then we store it, so we end up with the list of rays
                    // We'll then be able to remove rays that are identical, to simplify things
                    sf::Vector2f vectorDirectionToPolygonEdge = Normale( clipedPol[ j ].position - fovOrigin );
                    vectorDirectionToPolygonEdge *= float( fieldofview->mDistance );

                    // There it is
                    cRay ray( cEdgeF::MakePointDirection( fovOrigin, vectorDirectionToPolygonEdge ), cRay::eRayType::kBasicRay );

                    if( AddElementToVectorUnique( ray, &rayList ) )
                        mDEBUGRays.push_back( ray.mRay );
                }

                // Then we intersect every rays against polygon
                // ============================================
                // ============================================
                for( auto ray : rayList )
                {
                    // Now, for each edge of the clipped polygon, we intersect with that ray
                    // and harvest all intersections
                    std::vector< cEdgeF > clipPolEdges;

                    // Collision between ray and clipped Polygon will be stored in this vertexArray
                    sf::VertexArray hitPoints;
                    bool onlyVertexIntersection = true; // To quickly know if hitpoints are only vertex exact, or if some are mid-edge intersections

                    ExtractEdgesFromPolygon( &clipPolEdges, clipedPol );
                    for( auto edge : clipPolEdges )
                    {
                        float paramA;
                        float paramB;

                        if( cEdgeF::Intersect( &paramA, &paramB, edge, ray.mRay ) )
                        {
                            if( ( paramA > kEpsilonF && paramA < 1.0F - kEpsilonF ) // If actual intersection that is NOT on an exact vertex
                                && ( paramB > kEpsilonF && paramB < 1.0F - kEpsilonF ) )
                            {
                                //mDEBUGHitPoints.append( ray.mPoint + paramB * ray.mDirection );
                                //mDEBUGHitPoints[ mDEBUGHitPoints.getVertexCount() - 1 ].color = sf::Color::Red;
                                hitPoints.append( ray.mRay.mPoint + paramB * ray.mRay.mDirection );
                                onlyVertexIntersection = false;
                            }
                            else if( abs(paramA) < kEpsilonF || abs(paramA - 1.0F) < kEpsilonF ) // If it is on an exact vertex
                            {
                                //mDEBUGHitPoints.append( ray.mPoint + paramB * ray.mDirection );
                                //mDEBUGHitPoints[ mDEBUGHitPoints.getVertexCount() - 1 ].color = sf::Color::Green;

                                sf::Vector2f vertex = ray.mRay.mPoint + paramB * ray.mRay.mDirection;
                                AddElementToVertexArrayUnique( vertex, &hitPoints );
                            }
                        }
                    }

                    // If only one local or no intersections with polygon, it means the ray will cast up to the fov's limit
                    // So the interesting hitpoint of that ray is fov's limit
                    if( hitPoints.getVertexCount() <= 1 )
                    {
                        // We get fov's limit, which is the edge 1-2 (0 is always the origin point of fov)
                        // Then we intersect with the ray to get the exact point
                        cEdgeF fovLimit = cEdgeF::MakePointPoint( mTriangles[ i ][1].position, mTriangles[ i ][2].position );
                        float paramA;
                        float paramB;
                        cEdgeF::Intersect( &paramA, &paramB, fovLimit, ray.mRay );

                        auto fovVector = ray.mRay.mPoint + paramB * ray.mRay.mDirection;
                        AddElementToVertexArrayUnique( fovVector, &mInterestingHitPoints );

                        // CHECK: we could remove this from if
                        // BUT: this situation avoids computing useless transformations and apply a useless sort
                        // We also push the single intersection, to be able to build subTriangles
                        if( hitPoints.getVertexCount() == 1 )
                        {
                            // If the point is not added, it means it's already there, which means fovIntersection is the same point as the vertex itself
                            if( !AddElementToVertexArrayUnique( hitPoints[ 0 ].position, &mInterestingHitPoints ) )
                            {
                                idPoint = fovVector;
                                vertexIntersectionAndFovInterAreIdentical = true;
                            }
                        }
                    }
                    else if( hitPoints.getVertexCount() > 1 )
                    {
                        if( onlyVertexIntersection && ray.mRayType == cRay::eRayType::kBasicRay /*&& consecutives*/ )
                        {
                            bool consec = true;
                            for( int k = 0; k < hitPoints.getVertexCount() - 1; ++k )
                            {
                                if( !VertexesAreNeighboorInPolygon( clipedPol, hitPoints[ k ].position, hitPoints[ k + 1 ].position ) )
                                {
                                    consec = false;
                                    break;
                                }
                            }
                            if( consec )
                            {
                                // We get fov's limit, which is the edge 1-2 (0 is always the origin point of fov)
                                // Then we intersect with the ray to get the exact point
                                cEdgeF fovLimit = cEdgeF::MakePointPoint( mTriangles[ i ][ 1 ].position, mTriangles[ i ][ 2 ].position );
                                float paramA;
                                float paramB;
                                cEdgeF::Intersect( &paramA, &paramB, fovLimit, ray.mRay );

                                auto fovVector = ray.mRay.mPoint + paramB * ray.mRay.mDirection;
                                AddElementToVertexArrayUnique( fovVector, &mInterestingHitPoints );
                            }
                        }

                        // If there were more than one intersection, we keep the closest one
                        // So we transform points into watcher's referential
                        // That has its fov pointing upwards => the smallest the X, the closest it is
                        TransformPolygonUsingTransformation( &hitPoints, mTransformationAngleSort );
                        hitPoints = SortVertexesByX( hitPoints );
                        TransformPolygonUsingTransformation( &hitPoints, mTransformationAngleSort.getInverse() );
                        mInterestingHitPoints.append( hitPoints[ 0 ].position );

                    }
                }

                TransformPolygonUsingTransformation( &mInterestingHitPoints, mTransformationAngleSort );
                mInterestingHitPoints = SortVertexesByAngle( mInterestingHitPoints );
                TransformPolygonUsingTransformation( &mInterestingHitPoints, mTransformationAngleSort.getInverse() );
                // Need to retransform mInteresing points ?

                // Now, one last part before creating sub triangles :
                // There are up to 2 cases max where 2 hitpoints are aligned
                // It is when a ray is casted on a vertex that is the visible limit of the polygon from the watcher
                // The angle sort will, in case of equal angles, push the closest one before the further one
                // But in order to create sub triangles, we possibly need one pair of hit point to be swaped ( the furthest one gets before the closest )
                // The case is when the right part of the fov didn't intersect with the polygon.
                // Then, the first pair of aligned hitpoints need to be swaped


                // End point of right fov
                sf::Vector2f endPoint = mTriangles[ i ][ 1 ].position;

                bool rightFovCollided = true;
                // If that end point is a point of interest, it means that that ray didn't intersect with the polygon
                // So we'll swap the first pair of aligned HP
                for( int i = 0; i < mInterestingHitPoints.getVertexCount(); ++i )
                {
                    sf::Vector2f subtract = mInterestingHitPoints[ i ].position - endPoint;
                    if( abs(subtract.x) < kEpsilonF && abs( subtract.y) < kEpsilonF )
                    {
                        rightFovCollided = false;
                        break;
                    }
                }

                // If we didn't have an intersection with right part fov and polygon, then the next two hit points are
                // necessarily the aligned pair
                // so we swap 1 and 2 ( 0 is the end point of right fov ray)
                if( !rightFovCollided )
                {
                    if( mInterestingHitPoints.getVertexCount() >= 3 ) // safety
                    {
                        if( (!vertexIntersectionAndFovInterAreIdentical)
                            ||
                            (vertexIntersectionAndFovInterAreIdentical
                            && !IsVectorEqualToVector( mInterestingHitPoints[ 1 ].position, idPoint ) ) )
                        {
                            sf::Vector2f tmp = mInterestingHitPoints[ 1 ].position;
                            mInterestingHitPoints[ 1 ].position = mInterestingHitPoints[ 2 ].position;
                            mInterestingHitPoints[ 2 ].position = tmp;
                        }
                    }
                }

                // Now all is ready for sub triangles creation
                // We'll encounter 2x triangles that are flat ( the aligned hit points )
                // So, don't forget to check for these and don't add them in the sub set
                sf::VertexArray subTriangle( sf::Triangles, 3 );
                subTriangle[ 0 ] = fovOrigin;

                for( int i = 0; i < mInterestingHitPoints.getVertexCount() - 1; ++i )
                {
                    subTriangle[ 1 ] = mInterestingHitPoints[ i ];
                    subTriangle[ 2 ] = mInterestingHitPoints[ i + 1 ];

                    if( !Collinear( subTriangle[ 1 ].position - subTriangle[ 0 ].position, subTriangle[ 2 ].position - subTriangle[ 0 ].position ) )
                        mResultingSubTriangles.push_back( subTriangle );
                }
            }
        }
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
        AcceptEntity( iEntity );
}

