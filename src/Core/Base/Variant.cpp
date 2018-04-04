#include "Variant.h"

#include <string>

template< type tType >
cPrimitiveType::~cPrimitiveType()
{
}


template< type tType >
cPrimitiveType::cPrimitiveType( tType& iValue ) :
    mValue( iValue )
{
}


// ==============================================================================================================
// ================================================================================================= Access / Get
// ==============================================================================================================


template< type tType >
tType
cPrimitiveType::GetValue() const
{
    return  mValue;
}


template< type tType >
void
cPrimitiveType::SetValue( const tType& iValue )
{
    mValue = iValue;
}


// ==============================================================================================================
// =============================================================================================== Input / Output
// ==============================================================================================================


template< type tType >
void
cVariant::SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument )
{
    iNode->SetAttribute( "value", mValue );
}


template< type tType >
void
cVariant::LoadXML( tinyxml2::XMLElement* iNode )
{
    if( !iNode->QueryValueAttribute( "value", &mValue ) )
        printf( "PrimitiveType Loading error !\n" );
}



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
}


// ==============================================================================================================
// ============================================================================================= Access / Getters
// ==============================================================================================================


eType
cVariant::Type()
{
    return  mType;
}


uAllTypes&
cVariant::Value()
{
    return  mValue;
}


void
cVariant::Value( uAllTypes& iValue )
{
    mValue = iValue;
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


