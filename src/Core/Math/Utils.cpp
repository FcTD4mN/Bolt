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
    float angle = a2 - a1;

    while( angle > kPIF )
        angle -= 2.0F * kPIF;

    while( angle < -kPIF )
        angle += 2.0F * kPIF;

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
        float angle = float(GetAngleBetweenVectors( firstVector, iPolygon[ i ].position - cog ));
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
                if( (parameterA >= 0.0F && parameterA <= 1.0F)
                    && parameterB >= 0.0F && parameterB <= 1.0F )
                {
                    intersectionList.append( polygonAEdges[ i ].mPoint + parameterA * polygonAEdges[ i ].mDirection );
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
        if( CCWWindedPolygonContainsPoint( iPolygonB, iPolygonA[ i ].position ) )
            intersectionList.append( iPolygonA[ i ].position );
    }

    for( int i = 0; i < iPolygonB.getVertexCount(); ++i )
    {
        if( CCWWindedPolygonContainsPoint( iPolygonA, iPolygonB[ i ].position ) )
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

        float angle = GetAngleBetweenVectors( v.mDirection, vecProjection );
        if( angle > 0.0F )
            return  false;
    }

    return  true;
}


void
ExtractEdgesFromPolygon( std::vector<cEdgeF>* oEdges, const sf::VertexArray& iPolygon )
{
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



// This functions clips all the edges w.r.t one clip
// edge of clipping area
void clip( sf::VertexArray& iPolygon, sf::Vector2f& iPt1, sf::Vector2f& iPt2 )
{
    //sf::VertexArray output( sf::PrimitiveType::Points, iPolygon.getVertexCount );

    //// (ix,iy),(kx,ky) are the co-ordinate values of
    //// the points
    //int polySize = iPolygon.getVertexCount();

    //for( int i = 0; i < iPolygon.getVertexCount(); ++i )
    //{
    //    // i and k form a line in polygon
    //    int k = ( i + 1 ) % polySize;
    //    int ix = iPolygon[ i ].position.x, iy = iPolygon[ i ].position.y;
    //    int kx = poly_points[ k ][ 0 ], ky = poly_points[ k ][ 1 ];

    //    // Calculating position of first point
    //    // w.r.t. clipper line
    //    int i_pos = ( x2 - x1 ) * ( iy - y1 ) - ( y2 - y1 ) * ( ix - x1 );

    //    // Calculating position of second point
    //    // w.r.t. clipper line
    //    int k_pos = ( x2 - x1 ) * ( ky - y1 ) - ( y2 - y1 ) * ( kx - x1 );

    //    // Case 1 : When both points are inside
    //    if( i_pos < 0 && k_pos < 0 )
    //    {
    //        //Only second point is added
    //        new_points[ new_poly_size ][ 0 ] = kx;
    //        new_points[ new_poly_size ][ 1 ] = ky;
    //        new_poly_size++;
    //    }

    //    // Case 2: When only first point is outside
    //    else if( i_pos >= 0 && k_pos < 0 )
    //    {
    //        // Point of intersection with edge
    //        // and the second point is added
    //        new_points[ new_poly_size ][ 0 ] = x_intersect( x1,
    //                                                        y1, x2, y2, ix, iy, kx, ky );
    //        new_points[ new_poly_size ][ 1 ] = y_intersect( x1,
    //                                                        y1, x2, y2, ix, iy, kx, ky );
    //        new_poly_size++;

    //        new_points[ new_poly_size ][ 0 ] = kx;
    //        new_points[ new_poly_size ][ 1 ] = ky;
    //        new_poly_size++;
    //    }

    //    // Case 3: When only second point is outside
    //    else if( i_pos < 0 && k_pos >= 0 )
    //    {
    //        //Only point of intersection with edge is added
    //        new_points[ new_poly_size ][ 0 ] = x_intersect( x1,
    //                                                        y1, x2, y2, ix, iy, kx, ky );
    //        new_points[ new_poly_size ][ 1 ] = y_intersect( x1,
    //                                                        y1, x2, y2, ix, iy, kx, ky );
    //        new_poly_size++;
    //    }

    //    // Case 4: When both points are outside
    //    else
    //    {
    //        //No points are added
    //    }
    //}

    //// Copying new points into original array
    //// and changing the no. of vertices
    //poly_size = new_poly_size;
    //for( int i = 0; i < poly_size; i++ )
    //{
    //    poly_points[ i ][ 0 ] = new_points[ i ][ 0 ];
    //    poly_points[ i ][ 1 ] = new_points[ i ][ 1 ];
    //}
}

//// Implements Sutherland–Hodgman algorithm
//void suthHodgClip( int poly_points[][ 2 ], int poly_size,
//                   int clipper_points[][ 2 ], int clipper_size )
//{
//    //i and k are two consecutive indexes
//    for( int i = 0; i<clipper_size; i++ )
//    {
//        int k = ( i + 1 ) % clipper_size;
//
//        // We pass the current array of vertices, it's size
//        // and the end points of the selected clipper line
//        clip( poly_points, poly_size, clipper_points[ i ][ 0 ],
//              clipper_points[ i ][ 1 ], clipper_points[ k ][ 0 ],
//              clipper_points[ k ][ 1 ] );
//    }
//
//    // Printing vertices of clipped polygon
//    for( int i = 0; i < poly_size; i++ )
//        cout << '(' << poly_points[ i ][ 0 ] <<
//        ", " << poly_points[ i ][ 1 ] << ") ";
//}
//
////Driver code
//int main()
//{
//    // Defining polygon vertices in clockwise order
//    int poly_size = 3;
//    int poly_points[ 20 ][ 2 ] = { { 100,150 },{ 200,250 },
//    { 300,200 } };
//
//    // Defining clipper polygon vertices in clockwise order
//    // 1st Example with square clipper
//    int clipper_size = 4;
//    int clipper_points[][ 2 ] = { { 150,150 },{ 150,200 },
//    { 200,200 },{ 200,150 } };
//
//    // 2nd Example with triangle clipper
//    /*int clipper_size = 3;
//    int clipper_points[][2] = {{100,300}, {300,300},
//    {200,100}};*/
//
//    //Calling the clipping function
//    suthHodgClip( poly_points, poly_size, clipper_points,
//                  clipper_size );
//
//    return 0;
//}



//...