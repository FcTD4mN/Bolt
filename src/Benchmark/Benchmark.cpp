#include "Benchmark.h"
#include <iostream>
#include <chrono>
#include <vector>
#include <unordered_map>
#include <map>
#include <string>

#include <windows.h>

namespace  nBenchmark
{
	struct  cVectorEntry
	{
		std::string key;
		int			value;
	};

	void Benchmark( int iSize, long long* oVecResult, long long* oHMapResult, long long* oMapResult )
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

		Sleep( 2 );


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

		Sleep( 2 );


		start = std::chrono::high_resolution_clock::now();
		auto temp = hMap.find( LAST_STR );
		end = std::chrono::high_resolution_clock::now() - start;
		// std::cout << "hMap : " << std::to_string( end.count() ) << std::endl;

		*oHMapResult = end.count();

		Sleep( 2 );

		start = std::chrono::high_resolution_clock::now();
		auto temp2 = map.find( LAST_STR );
		end = std::chrono::high_resolution_clock::now() - start;
		// std::cout << "map : " << std::to_string( end.count() ) << std::endl;

		*oMapResult = end.count();
	}

	void Run()
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
			Benchmark( size, &currentvecresult, &currenthmapresult, &currentmapresult );

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

}  // namespace  nBenchmark

