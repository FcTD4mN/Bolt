 #include "Core.ECS.Component.UserInput.h"


namespace nCore {
namespace nECS {
namespace nComponent {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cUserInput::~cUserInput()
{
}


cUserInput::cUserInput() :
    tSuperClass( "userinput" )
{
}


cUserInput::cUserInput( const cUserInput & iUserInput ) :
    tSuperClass( iUserInput )
{
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------- Copy
// -------------------------------------------------------------------------------------


::nCore::nECS::nCore::cComponent*
cUserInput::Clone() const
{
    return  new cUserInput( *this );
}


bool
cUserInput::ContainsAction( const std::string & iAction ) const
{
    for( int i = 0; i < mActions.size(); ++i )
    {
        if( mActions[ i ] == iAction )
            return  true;
    }

    return false;
}


} // namespace nComponent
} // namespace nECS
} // namespace nCore

