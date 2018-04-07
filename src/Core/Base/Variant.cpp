#include "Variant.h"

#include <string>


namespace nBase {

cNumber::~cNumber()
{
}


cNumber::cNumber( double iValue ) :
    tSuperClass( iValue )
{
}


// ==============================================================================================================
// =============================================================================================== Input / Output
// ==============================================================================================================


void
cNumber::SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument )
{
    iNode->SetAttribute( "value", mValue );
}


void
cNumber::LoadXML( tinyxml2::XMLElement* iNode )
{
    mValue = iNode->DoubleAttribute( "value", 0.0 );
}



// ===================================
// ===================================
// ===================================



cString::~cString()
{
}

cString::cString( const std::string & iValue ) :
    tSuperClass( iValue )
{
}


// ==============================================================================================================
// =============================================================================================== Input / Output
// ==============================================================================================================


void
cString::SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument )
{
    iNode->SetAttribute( "value", mValue.c_str() );
}


void
cString::LoadXML( tinyxml2::XMLElement* iNode )
{
    mValue = iNode->Attribute( "value", "" );
}



// ==============================================================================================================
// ==============================================================================================================
// ==============================================================================================================
// ==============================================================================================================
// ==============================================================================================================
// ==============================================================================================================
// ==============================================================================================================
// ==============================================================================================================
// ==============================================================================================================
// ==============================================================================================================
// ==============================================================================================================


cVariant::~cVariant()
{
}


cVariant::cVariant() :
    mType( kInvalid )
{
}


cVariant::cVariant( eType iType ) :
    mType( iType )
{
    switch( iType )
    {
        case kNumber :
            mValue.mNumber = cNumber( 0 );
            break;

        case kString :
            mValue.mString = cString( "" );
            break;

        default:
            printf( "Invalid variant type\n" );
            break;
    }
}


// ==============================================================================================================
// ============================================================================================= Access / Getters
// ==============================================================================================================


eType
cVariant::Type()
{
    return  mType;
}


double
cVariant::GetValueNumber() const
{
    return  mValue.mNumber.GetValue();
}


std::string
cVariant::GetValueString() const
{
    return  mValue.mString.GetValue();
}


void
cVariant::SetValueNumber( double iValue )
{
    mValue.mNumber = iValue;
}


void
cVariant::SetValueString( std::string& iValue )
{
    mValue.mString = iValue;
}


// ==============================================================================================================
// =============================================================================================== Input / Output
// ==============================================================================================================


void
cVariant::SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument )
{
    iNode->SetAttribute( "type", mType );
    switch( mType )
    {
        case eType::kNumber :
            mValue.mNumber.SaveXML( iNode, iDocument );
            break;
        case eType::kString :
            mValue.mString.SaveXML( iNode, iDocument );
            break;

        default:
            break;
    }
}


void
cVariant::LoadXML( tinyxml2::XMLElement* iNode )
{
    mType = eType( iNode->IntAttribute( "type", 0 ) );
    switch( mType )
    {
        case eType::kNumber :
            mValue.mNumber.LoadXML( iNode );
            break;
        case eType::kString :
            mValue.mString.LoadXML( iNode );
            break;

        default:
            break;
    }
}

} //nBase
