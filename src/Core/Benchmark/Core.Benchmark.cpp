#include "Core.Benchmark.h"


#include "Core.ECS.Core.World.h"
#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Core.Component.h"

#include "Core.ECS.Component.Color.h"
#include "Core.ECS.Component.Position.h"
#include "Core.ECS.Component.Size.h"
#include "Core.ECS.Component.Text.h"

#include "Core.ECS.System.InputConverter.h"
#include "Core.ECS.System.SimplerRenderer.h"


#include <iostream>
#include <chrono>
#include <vector>
#include <unordered_map>
#include <map>
#include <string>
#include <thread>

#ifdef WINDOWS
#include <windows.h>
#endif // WINDOWS


namespace  nBenchmark {


struct  cVectorEntry
{
    std::string key;
    int            value;
};

void VectorVsHMapvsMapBenchmark( int iSize, long long* oVecResult, long long* oHMapResult, long long* oMapResult )
{
    int SIZE = iSize;
    int LAST = SIZE-1;
    std::string LAST_STR = std::to_string( LAST );

    std::vector< cVectorEntry > vec ( SIZE );
    std::unordered_map<std::string, int> hMap;
    std::map< std::string, int > map;
    for ( int i = 0; i < SIZE; ++i )
    {
        cVectorEntry vectorEntry;
        vectorEntry.key = std::to_string( i );
        vectorEntry.value = i;
        vec.push_back( vectorEntry );
        hMap[ std::to_string( i ) ] = i;
        map[ std::to_string( i ) ] = i;
    }

#ifdef WINDOWS
    Sleep( 2 );
#else
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
#endif // WINDOWS


    auto start = std::chrono::high_resolution_clock::now();
    for ( int i = 0; i < SIZE; ++i )
    {
        if ( vec[i].key == LAST_STR )
        {
            break;
        }
    }
    auto end = std::chrono::high_resolution_clock::now() - start;
    // std::cout << "vector : " << std::to_string( end.count() ) << std::endl;

    *oVecResult = end.count();

#ifdef WINDOWS
    Sleep( 2 );
#else
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
#endif // WINDOWS

    start = std::chrono::high_resolution_clock::now();
    auto temp = hMap.find( LAST_STR );
    end = std::chrono::high_resolution_clock::now() - start;
    // std::cout << "hMap : " << std::to_string( end.count() ) << std::endl;

    *oHMapResult = end.count();

#ifdef WINDOWS
    Sleep( 2 );
#else
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
#endif // WINDOWS

    start = std::chrono::high_resolution_clock::now();
    auto temp2 = map.find( LAST_STR );
    end = std::chrono::high_resolution_clock::now() - start;
    // std::cout << "map : " << std::to_string( end.count() ) << std::endl;

    *oMapResult = end.count();
}

void RunVectorVsHMapvsMapBenchmark()
{
    long long vecresult = 0;
    long long hmapresult = 0;
    long long mapresult = 0;
    int nIterations = 1000;
    for( int i = 1; i <= nIterations; ++ i )
    {
        int size = 50;

        long long currentvecresult = 0;
        long long currenthmapresult = 0;
        long long currentmapresult = 0;
        VectorVsHMapvsMapBenchmark( size, &currentvecresult, &currenthmapresult, &currentmapresult );

        vecresult += currentvecresult;
        hmapresult += currenthmapresult;
        mapresult  += currentmapresult;
        printf( "%d\n", i );
    }

    vecresult  /= nIterations;
    hmapresult /= nIterations;
    mapresult  /= nIterations;

    std::cout << "vec:" << std::to_string( vecresult ) << std::endl;
    std::cout << "hmap:" << std::to_string( hmapresult ) << std::endl;
    std::cout << "map:" << std::to_string( mapresult ) << std::endl;

    int dummy = 0;
    std::cin >> dummy;
}


void EntityStressTest()
{
    ::nECS::cWorld* world = new ::nECS::cWorld();

    auto start = std::chrono::high_resolution_clock::now();

    for( int i = 1; i <= 100; ++i )
    {
        ::nECS::cEntity* ent = new ::nECS::cEntity();
        ent->AddComponent( new ::nECS::cSize( 10.0F, 10.0F ) );
        ent->AddComponent( new ::nECS::cPosition( 10.0F, 100.0F ) );
        ent->AddComponent( new ::nECS::cText( "Test" ) );
        ent->AddComponent( new ::nECS::cColor( 255, 255, 0, 255 ) );

        world->AddEntity( ent );

        world->AddSystem( new ::nECS::cInputConverter() );
        world->AddSystem( new ::nECS::cSimplerRenderer() );
    }

    auto end = std::chrono::high_resolution_clock::now() - start;
    std::cout << "Creation time : " << std::to_string( end.count() ) << std::endl;


    start = std::chrono::high_resolution_clock::now();

    for( int i = 1; i <= 1000; ++i )
        world->Update( i );

    end = std::chrono::high_resolution_clock::now() - start;
    std::cout << "Run time : " << std::to_string( end.count() ) << std::endl;
}


void DrawStressTest( sf::RenderTarget* iRender )
{
    int COUNT = 20000;
    sf::RectangleShape rect( sf::Vector2f( 100.0F, 100.0F ) );
    rect.setFillColor( sf::Color( 255, 00, 00, 1 ) );
    rect.setPosition( sf::Vector2f( 400.0F, 300.0F ) );
    for( int i = 1; i <= COUNT; ++i )
    {
        iRender->draw( rect );
    }
}


}  // namespace  nBenchmark

