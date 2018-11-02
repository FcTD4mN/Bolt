#include "command.h"


#include "mod.h"


#include <fstream>
#include <iostream>


namespace nCore {
namespace nPyBoltECSAPI {


void
Init()
{
    PyImport_AppendInittab( "PyBoltECSAPI", &PyInit_PyBoltECSAPI );
}


void
ParseFile( const  std::string& iStr )
{
    Init();

    // Reading stream
    std::ifstream file( iStr.c_str() );

    // Error Handling
    if( !file )
    {
        std::cout << "Error, cannot find source file: " << iStr << std::endl;
        return;
    }

    // Stream to string
    std::string ligne;
    std::string codeSource;

    // Reading
    while( getline( file, ligne ) )
        codeSource += ligne + '\n';

    // Closing file
    file.close();

    PyRun_SimpleString( codeSource.c_str() );
}


void
Finalize()
{
    //NOTHING ATM
}


} // namespace nPyBoltECSAPI
} // namespace nCore

