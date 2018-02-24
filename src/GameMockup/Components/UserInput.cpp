 #include "UserInput.h"


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


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Input/Output
// -------------------------------------------------------------------------------------


void
cUserInput::SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument )
{
    tSuperClass::SaveXML( iNode, iDocument );
}


void
cUserInput::LoadXML( const tinyxml2::XMLElement* iNode )
{
    tSuperClass::LoadXML( iNode );
}



