#include "Math/Utils.h"

bool IsPointInTriangle( sf::Vector2f& pt, sf::Vector2f& v1, sf::Vector2f& v2, sf::Vector2f& v3 )
{
    bool b1, b2, b3;

    b1 = Sign( pt, v1, v2 ) < 0.0f;
    b2 = Sign( pt, v2, v3 ) < 0.0f;
    b3 = Sign( pt, v3, v1 ) < 0.0f;

    return ( ( b1 == b2 ) && ( b2 == b3 ) );
}


double
GetAngleBetweenVectors( const sf::Vector2f& p1, const sf::Vector2f& p2 )
{
    float a1 = atan2( p1.y, p1.x );
    float a2 = atan2( p2.y, p2.x );
    float angle = a1 - a2;

    while( angle > kPIF )
        angle -= 2.0F * kPIF;

    while( angle < -kPIF )
        angle += 2.0F * kPIF;

    return  angle;
}


double
GetAngleBetweenVectors2( const sf::Vector2f& p1, const sf::Vector2f& p2 )
{
    float a1 = atan2( p1.y, p1.x );
    float a2 = atan2( p2.y, p2.x );
    float angle = a1 - a2;
    return  angle;
}


sf::Vector2f CenterOfGravity( const sf::VertexArray & iPolygon )
{
    sf::Vector2f cog( 0.0F, 0.0F );
    for( int i = 0; i < iPolygon.getVertexCount(); ++i )
        cog += iPolygon[ i ].position;

    cog /= float(iPolygon.getVertexCount());

    return  cog;
}


sf::VertexArray PolygonPolygonInterectionList( const sf::VertexArray & iPolygonA, const sf::VertexArray & iPolygonB )
{
    sf::VertexArray intersectionList;
    std::vector< cEdgeF > polygonAEdges;
    std::vector< cEdgeF > polygonBEdges;

    ExtractEdgesFromPolygon( &polygonAEdges, iPolygonA );
    ExtractEdgesFromPolygon( &polygonBEdges, iPolygonB );

    for( int i = 0; i < polygonAEdges.size(); ++i )
    {
        for( int j = 0; j < polygonBEdges.size(); ++j )
        {
            float parameterA = 0.0F;
            float parameterB = 0.0F;
            if( cEdgeF::Intersect( &parameterA, &parameterB, polygonAEdges[ i ], polygonBEdges[ j ] ) )
            {
                sf::Vector2f interPt = polygonAEdges[ i ].mPoint + parameterA * polygonAEdges[ i ].mDirection;

                if( (parameterA >= 0.0F && parameterA <= 1.0F)
                    && parameterB >= 0.0F && parameterB <= 1.0F
                    && !VertexArrayContainsVertex( intersectionList, interPt ) )
                {
                    intersectionList.append( interPt );
                }
            }
        }
    }

    return  intersectionList;
}


sf::VertexArray ClipPolygonPolygon( const sf::VertexArray& iPolygonA, const sf::VertexArray& iPolygonB )
{
    sf::VertexArray intersectionList = PolygonPolygonInterectionList( iPolygonA, iPolygonB );

    for( int i = 0; i < iPolygonA.getVertexCount(); ++i )
    {
        if( CCWWindedPolygonContainsPoint( iPolygonB, iPolygonA[ i ].position )
                && !VertexArrayContainsVertex( intersectionList, iPolygonA[ i ].position ) )
            intersectionList.append( iPolygonA[ i ].position );
    }

    for( int i = 0; i < iPolygonB.getVertexCount(); ++i )
    {
        if( CCWWindedPolygonContainsPoint( iPolygonA, iPolygonB[ i ].position )
            && !VertexArrayContainsVertex( intersectionList, iPolygonB[ i ].position ) )
            intersectionList.append( iPolygonB[ i ].position );
    }

    return  CCWWindingSort( intersectionList );
}


bool
CCWWindedPolygonContainsPoint( const sf::VertexArray & iPolygon, const sf::Vector2f & iPoint )
{
    std::vector< cEdgeF > edgeList;
    ExtractEdgesFromPolygon( &edgeList, iPolygon );

    for( auto v : edgeList )
    {
        sf::Vector2f normal = Orthogonal( v.mDirection );
        cEdgeF orthogonalite( cEdgeF::MakePointDirection( iPoint, normal ) );

        float parameterA = 0.0F;
        float parameterB = 0.0F;

        cEdgeF::Intersect( &parameterA, &parameterB, v, orthogonalite );
        sf::Vector2f projection = v.mPoint + parameterA * v.mDirection;

        sf::Vector2f vecProjection = iPoint - projection;

        double angle = GetAngleBetweenVectors( v.mDirection, vecProjection );
        if( angle < 0.0 )
            return  false;
    }

    return  true;
}


void
ExtractEdgesFromPolygon( std::vector<cEdgeF>* oEdges, const sf::VertexArray& iPolygon )
{
    if( iPolygon.getVertexCount() == 0 )
        return;

    (*oEdges).clear();
    (*oEdges).reserve( iPolygon.getVertexCount() );

    for( int i = 0; i < iPolygon.getVertexCount() - 1; ++i )
    {
        (*oEdges).push_back( cEdgeF::MakePointPoint( iPolygon[ i ].position, iPolygon[ i + 1 ].position ) );
    }
    (*oEdges).push_back( cEdgeF::MakePointPoint( iPolygon[ iPolygon.getVertexCount() - 1 ].position, iPolygon[ 0 ].position ) );
}


sf::FloatRect
GetTriangleSetBBox( const std::vector< sf::VertexArray >& iTriangleSet )
{
    if( iTriangleSet.size() == 0 )
        return  sf::FloatRect( 0.0f, 0.0f, 0.0f, 0.0f );

    sf::FloatRect bBox = iTriangleSet[ 0 ].getBounds();
    float x = bBox.left;
    float y = bBox.top;
    float x2 = bBox.left + bBox.width;
    float y2 = bBox.top + bBox.height;

    for( int i = 1; i < iTriangleSet.size(); ++i )
    {
        bBox = iTriangleSet[ i ].getBounds();
        if( x > bBox.left )
            x = bBox.left;
        if( y > bBox.top )
            y = bBox.top;
        if( x2 < bBox.left + bBox.width )
            x2 = bBox.left + bBox.width;
        if( y2 < bBox.top + bBox.height )
            y2 = bBox.top + bBox.height;
    }
    return  sf::FloatRect( x, y , x2 - x, y2 - y );
}


void
GetPolygonExtremesByAngle( sf::Vector2f* oMinVertex, sf::Vector2f* oMaxVertex, const sf::VertexArray& iPolygon )
{
    if( iPolygon.getVertexCount() == 0 )
    {
        ( *oMinVertex ) = sf::Vector2f( 0.0F, 0.0F );
        ( *oMaxVertex ) = sf::Vector2f( 0.0F, 0.0F );
        return;
    }

    sf::VertexArray  sortedVertexes = SortVertexesByAngle( iPolygon );

    ( *oMinVertex ) = sortedVertexes[ 0 ].position;
    ( *oMaxVertex ) = sortedVertexes[ sortedVertexes.getVertexCount() - 1 ].position;

    double angleMax = GetAngleBetweenVectors2( gXAxisVector, sortedVertexes[ sortedVertexes.getVertexCount() - 1 ].position );

    for( int i = int(sortedVertexes.getVertexCount() - 1); i >= 0; --i )
    {
        double angle = GetAngleBetweenVectors2( gXAxisVector, sortedVertexes[ i ].position );
        if( abs( angle - angleMax ) > kEpsilonF )
            break;
        ( *oMaxVertex ) = sortedVertexes[ i ].position;
    }
}


sf::VertexArray
GetPointsFromPolygonInBetweenVectorsCCW( const sf::VertexArray & iPolygon, const sf::Vector2f & iFirstPoint, const sf::Vector2f & iSecondPoint )
{
    sf::VertexArray output;
    if( iPolygon.getVertexCount() < 3 ) // Won't be any points in between if only 2 points or less
        return  output;

    int firstIndex = -1;
    // This assumes the polygon IS ALREADY ccw sorted
    for( int i = 0; i < iPolygon.getVertexCount(); ++i )
    {
        if( IsVectorEqualToVector( iFirstPoint, iPolygon[ i ].position ) )
        {
            firstIndex = i;
            break;
        }
    }

    int current = (firstIndex + 1) % iPolygon.getVertexCount();
    while( !IsVectorEqualToVector( iSecondPoint, iPolygon[ current ].position ) )
    {
        output.append( iPolygon[ current ] );
        current = (current + 1) % iPolygon.getVertexCount();
    }

    return  output;
}


void
TriangleSubDivisionUsingPolygon( std::vector< sf::VertexArray >* oSubTrianglesOutput, const sf::VertexArray& iTriangle, const sf::VertexArray& iPolygon )
{
    oSubTrianglesOutput->clear();

    sf::VertexArray clipedPol = ClipPolygonPolygon( iPolygon, iTriangle );
    // If this part of the fov doesn't clip with the polygon, we keep the whoe triangle, and we continue
    if( clipedPol.getVertexCount() == 0 )
    {
        oSubTrianglesOutput->push_back( iTriangle );
        return;
    }

    // End points of right fov
    sf::Vector2f fovOrigin = iTriangle[ 0 ].position;
    sf::Vector2f fovRightEndPoint = iTriangle[ 1 ].position;
    sf::Vector2f fovLeftEndPoint = iTriangle[ 2 ].position;

    // We compute the transformation that will put right side
    // of i-th triangle on x axis. This prevents any angle around PI
    sf::Transform transformation;
    transformation.rotate( float( RadToDeg( GetAngleBetweenVectors( gXAxisVector, fovRightEndPoint - fovOrigin ) ) ) );
    transformation.translate( -fovOrigin );

    // First we transpose clipedPolygon into watcher's referential, to get extreme points
    TransformPolygonUsingTransformation( &clipedPol, transformation );

    sf::Vector2f mostLeftPointOfClipedPoly;
    sf::Vector2f mostRightPointOfClipedPoly;
    GetPolygonExtremesByAngle( &mostRightPointOfClipedPoly, &mostLeftPointOfClipedPoly, clipedPol );

    mostLeftPointOfClipedPoly = transformation.getInverse().transformPoint( mostLeftPointOfClipedPoly );
    mostRightPointOfClipedPoly = transformation.getInverse().transformPoint( mostRightPointOfClipedPoly );

    TransformPolygonUsingTransformation( &clipedPol, transformation.getInverse() );

    // For both extreme points, we cast a ray towards them
    cRay rayRight( cEdgeF::MakePointPoint( fovOrigin, mostRightPointOfClipedPoly ), cRay::eRayType::kBasicRay );
    cRay rayLeft( cEdgeF::MakePointPoint( fovOrigin, mostLeftPointOfClipedPoly ), cRay::eRayType::kBasicRay );

    // We also get the fov limit edge
    cEdgeF fovLimit = cEdgeF::MakePointPoint( fovRightEndPoint, fovLeftEndPoint );

    // Then we get both points that intersect between ray and limit
    float paramA;
    float paramB;

    cEdgeF::Intersect( &paramA, &paramB, rayRight.mRay, fovLimit );
    sf::Vector2f fovHPRight = rayRight.mRay.mPoint + paramA * rayRight.mRay.mDirection;

    cEdgeF::Intersect( &paramA, &paramB, rayLeft.mRay, fovLimit );
    sf::Vector2f fovHPLeft = rayLeft.mRay.mPoint + paramA * rayLeft.mRay.mDirection;

    sf::VertexArray subTriangle( sf::Triangles, 3 );
    subTriangle[ 0 ] = fovOrigin;

    double angleToRight = GetAngleBetweenVectors( fovRightEndPoint - fovOrigin, fovHPRight - fovOrigin );
    if( angleToRight > kEpsilonF )
    {
        subTriangle[ 1 ] = fovRightEndPoint;
        subTriangle[ 2 ] = fovHPRight;

        if( !Collinear( subTriangle[ 1 ].position - subTriangle[ 0 ].position, subTriangle[ 2 ].position - subTriangle[ 0 ].position ) )
            ( *oSubTrianglesOutput ).push_back( subTriangle );
    }

    double angleToLeft = GetAngleBetweenVectors( fovHPLeft - fovOrigin, fovLeftEndPoint - fovOrigin );
    if( angleToLeft > kEpsilonF )
    {
        subTriangle[ 1 ] = fovHPLeft;
        subTriangle[ 2 ] = fovLeftEndPoint;

        if( !Collinear( subTriangle[ 1 ].position - subTriangle[ 0 ].position, subTriangle[ 2 ].position - subTriangle[ 0 ].position ) )
            ( *oSubTrianglesOutput ).push_back( subTriangle );
    }

    sf::VertexArray inBetweens = GetPointsFromPolygonInBetweenVectorsCCW( clipedPol, mostLeftPointOfClipedPoly, mostRightPointOfClipedPoly );
    if( inBetweens.getVertexCount() > 0 )
    {
        subTriangle[ 1 ] = inBetweens[ 0 ];
        subTriangle[ 2 ] = mostLeftPointOfClipedPoly;

        if( !Collinear( subTriangle[ 1 ].position - subTriangle[ 0 ].position, subTriangle[ 2 ].position - subTriangle[ 0 ].position ) )
            ( *oSubTrianglesOutput ).push_back( subTriangle );

        for( int i = 0; i < inBetweens.getVertexCount() - 1; ++i )
        {
            subTriangle[ 1 ] = inBetweens[ i + 1 ].position;
            subTriangle[ 2 ] = inBetweens[ i ].position;

            if( !Collinear( subTriangle[ 1 ].position - subTriangle[ 0 ].position, subTriangle[ 2 ].position - subTriangle[ 0 ].position ) )
                ( *oSubTrianglesOutput ).push_back( subTriangle );
        }

        subTriangle[ 1 ] = mostRightPointOfClipedPoly;
        subTriangle[ 2 ] = inBetweens[ inBetweens.getVertexCount() - 1 ];

        if( !Collinear( subTriangle[ 1 ].position - subTriangle[ 0 ].position, subTriangle[ 2 ].position - subTriangle[ 0 ].position ) )
            ( *oSubTrianglesOutput ).push_back( subTriangle );
    }
    else
    {
        subTriangle[ 1 ] = mostRightPointOfClipedPoly;
        subTriangle[ 2 ] = mostLeftPointOfClipedPoly;

        if( !Collinear( subTriangle[ 1 ].position - subTriangle[ 0 ].position, subTriangle[ 2 ].position - subTriangle[ 0 ].position ) )
            ( *oSubTrianglesOutput ).push_back( subTriangle );
    }
}


void
TriangleSubDivisionUsingPolygonMultiThreadCall( std::vector<sf::VertexArray>* oSubTrianglesOutput, const sf::VertexArray * iTriangle, const sf::VertexArray * iPolygon )
{
    TriangleSubDivisionUsingPolygon( oSubTrianglesOutput, *iTriangle, *iPolygon );
}


sf::VertexArray
CCWWindingSort( const sf::VertexArray & iPolygon )
{
    sf::VertexArray output( sf::PrimitiveType::Points );

    if( iPolygon.getVertexCount() == 0 )
        return  output;

    sf::Vector2f cog = CenterOfGravity( iPolygon );
    sf::Vector2f firstVector = iPolygon[ 0 ].position - cog;

    std::vector< sf::Vector2f > outputList;
    outputList.reserve( iPolygon.getVertexCount() );
    std::vector< float > angles;
    angles.reserve( iPolygon.getVertexCount() );

    angles.push_back( 0.0F );
    outputList.push_back( iPolygon[ 0 ].position );

    for( int i = 1; i < iPolygon.getVertexCount(); ++i )
    {
        float angle = float( GetAngleBetweenVectors( firstVector, iPolygon[ i ].position - cog ) );
        int j = 0;
        while( j < angles.size() && angle > angles[ j ] )
        {
            ++j;
        }
        angles.insert( angles.begin() + j, angle );
        outputList.insert( outputList.begin() + j, iPolygon[ i ].position );
    }

    for( auto v : outputList )
    {
        output.append( v );
    }

    return  output;
}


sf::VertexArray
SortVertexesByX( const sf::VertexArray& iPolygon )
{
    sf::VertexArray output;
    if( iPolygon.getVertexCount() <= 0 )
        return  output;

    if( iPolygon.getVertexCount() == 1 )
    {
        output = iPolygon;
        return  output;
    }

    output.resize( iPolygon.getVertexCount() );
    std::vector< sf::Vector2f > xSort;
    xSort.reserve( iPolygon.getVertexCount() );

    for( int i = 0; i < iPolygon.getVertexCount(); ++i )
    {
        int index = 0;
        while( index < xSort.size() && iPolygon[ i ].position.x > xSort[ index ].x )
            ++index;

        xSort.insert( xSort.begin() + index, iPolygon[ i ].position );
    }

    for( int i = 0; i < xSort.size(); ++i )
    {
        output[ i ].position = xSort[ i ];
    }

    return  output;
}


sf::VertexArray
SortVertexesByY( const sf::VertexArray & iPolygon )
{
    sf::VertexArray output;
    if( iPolygon.getVertexCount() <= 0 )
        return  output;

    if( iPolygon.getVertexCount() == 1 )
    {
        output = iPolygon;
        return  output;
    }

    output.resize( iPolygon.getVertexCount() );
    std::vector< sf::Vector2f > ySort;
    ySort.reserve( iPolygon.getVertexCount() );

    for( int i = 0; i < iPolygon.getVertexCount(); ++i )
    {
        int index = 0;
        while( index < ySort.size() && iPolygon[ i ].position.y > ySort[ index ].y )
            ++index;

        ySort.insert( ySort.begin() + index, iPolygon[ i ].position );
    }

    for( int i = 0; i < ySort.size(); ++i )
    {
        output[ i ].position = ySort[ i ];
    }

    return  output;
}


sf::VertexArray
SortVertexesByAngle( const sf::VertexArray& iPolygon )
{
    sf::VertexArray output( iPolygon.getPrimitiveType(), iPolygon.getVertexCount() );

    if( iPolygon.getVertexCount() == 0 )
        return  output;

    if( iPolygon.getVertexCount() == 1 )
    {
        output = iPolygon;
        return  output;
    }

    struct ePair
    {
        double angle;
        sf::Vector2f position;
    };

    std::vector< ePair > angleSort;
    angleSort.reserve( iPolygon.getVertexCount() );

    for( int i = 0; i < iPolygon.getVertexCount(); ++i )
    {
        ePair pair;
        pair.position = iPolygon[ i ].position;
        pair.angle = GetAngleBetweenVectors2( gXAxisVector, pair.position );

        int index = 0;

        bool equal = false;
        bool closer = false;

        while( ( ( index < angleSort.size() ) && ( abs( pair.angle - angleSort[ index ].angle ) < kEpsilonF ) )
               || ( ( index < angleSort.size() ) && ( pair.angle > angleSort[ index ].angle ) ) )
        {
            equal = abs( pair.angle - angleSort[ index ].angle ) < kEpsilonF;
            closer = pair.position.x < angleSort[ index ].position.x;

            if( equal && closer )
            {
                break;
            }
            else if( equal && !closer )
            {
                ++index;
                break;
            }

            ++index;
        }

        angleSort.insert( angleSort.begin() + index, pair );

    }

    for( int i = 0; i < angleSort.size(); ++i )
    {
        output[ i ] = angleSort[ i ].position;
    }

    return  output;
}


bool
VertexArrayContainsVertex( const  sf::VertexArray& iArray, const sf::Vector2f& iVector )
{
    for( int i = 0; i < iArray.getVertexCount(); ++i )
    {
        if( IsVectorEqualToVector( iVector, iArray[ i ].position ) )
            return  true;
    }

    return false;
}


bool
VertexesAreNeighboorInPolygon( const sf::VertexArray & iPolygon, const sf::Vector2f & iVectorA, const sf::Vector2f & iVectorB )
{
    int vertexAIndexInPolygon = -1;
    for( int i = 0; i < iPolygon.getVertexCount(); ++i )
    {
        if( IsVectorEqualToVector( iPolygon[ i ].position, iVectorA ) )
        {
            vertexAIndexInPolygon = i;
            break;
        }
    }

    int nextVertex = ( vertexAIndexInPolygon + 1 ) % iPolygon.getVertexCount();
    if( IsVectorEqualToVector( iPolygon[ nextVertex ].position, iVectorB ) )
        return  true;

    int previousVertex = ( vertexAIndexInPolygon - 1 );
    if( previousVertex < 0 )
        previousVertex = int(iPolygon.getVertexCount() - 1);
    if( IsVectorEqualToVector( iPolygon[ previousVertex ].position, iVectorB ) )
        return  true;

    return false;
}


void
TransformPolygonUsingTransformation( sf::VertexArray* oPolygon, const sf::Transform & iTransformation )
{
    for( int i = 0; i < (*oPolygon).getVertexCount(); ++i )
    {
        ( *oPolygon )[ i ].position = iTransformation.transformPoint( ( *oPolygon )[ i ].position );
    }
}


bool
AddElementToVertexArrayUnique( sf::Vector2f & iElement, sf::VertexArray * oVArray, int* oIndexOfExisting )
{
    *oIndexOfExisting = -1;
    for( int i = 0 ; i < (*oVArray).getVertexCount() ; ++i )
    {
        *oIndexOfExisting += 1;
        sf::Vector2f diff = (*oVArray)[ i ].position - iElement;
        if( abs( diff.x ) < kEpsilonPixelF && abs( diff.y ) < kEpsilonPixelF ) // vertexes are supposed to represent pixel points in the end, so 0.01 difference = same point
            return  false;
    }

    ( *oVArray ).append( iElement );
    return  true;
}


// Adds an element to a vector only if it is not already in
template<>
bool
AddElementToVectorUnique( sf::Vector2f& iElement, std::vector< sf::Vector2f >* oVector, int* oIndexOfExisting )
{
    *oIndexOfExisting = -1;
    for( auto elm : *oVector )
    {
        *oIndexOfExisting += 1;
        sf::Vector2f diff = elm - iElement;
        if( abs(diff.x) < kEpsilonPixelF && abs(diff.y) < kEpsilonPixelF ) // sfVector2f are supposed to represent pixel points in the end, so 0.01 difference = same point
            return  false;
    }

    ( *oVector ).push_back( iElement );
    return  true;
}


template<>
bool
AddElementToVectorUnique( cEdgeF & iElement, std::vector<cEdgeF>* oVector, int* oIndexOfExisting )
{
    *oIndexOfExisting = -1;
    for( auto elm : *oVector )
    {
        *oIndexOfExisting += 1;
        if( CollinearUsingAngles( iElement.mDirection, elm.mDirection ) || IsVectorEqualToVector( iElement.mDirection, elm.mDirection ) )
            return  false;
    }

    ( *oVector ).push_back( iElement );
    return  true;
}


template<>
bool
AddElementToVectorUnique( cRay& iElement, std::vector< cRay >* oVector, int* oIndexOfExisting )
{
    *oIndexOfExisting = -1;
    for( auto elm : *oVector )
    {
        *oIndexOfExisting += 1;
        if( CollinearUsingAngles( iElement.mRay.mDirection, elm.mRay.mDirection ) || IsVectorEqualToVector( iElement.mRay.mDirection, elm.mRay.mDirection ) )
            return  false;
    }

    ( *oVector ).push_back( iElement );
    return  true;
}


//...