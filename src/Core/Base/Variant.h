#include "tinyxml2.h"

#include <string>

namespace nBase {

enum eType
{
    kInvalid = 0,
    kNumber,
    kString
};

// Usefull for python essentially
template< typename T >
class cPrimitiveType
{
public:
    ~cPrimitiveType();
    cPrimitiveType( T iValue );

public:
    T       GetValue() const;
    void    SetValue( const T& iValue );

public:
    virtual  void SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument ) = 0; // Can't really be done templatly using tinyxml2
    virtual  void LoadXML( tinyxml2::XMLElement* iNode ) = 0; // Can't really be done templatly using tinyxml2

protected:
    T mValue;
};

//==============================================================================================================
//==============================================================================================================


template< typename T >
cPrimitiveType< T >::~cPrimitiveType()
{
}


template< typename T >
cPrimitiveType< T >::cPrimitiveType( T iValue ) :
    mValue( iValue )
{
}


// ==============================================================================================================
// ================================================================================================= Access / Get
// ==============================================================================================================


template< typename T >
T
cPrimitiveType< T >::GetValue() const
{
    return  mValue;
}


template< typename T >
void
cPrimitiveType< T >::SetValue( const T& iValue )
{
    mValue = iValue;
}


// ==============================================================================================================
// ==============================================================================================================
// ==============================================================================================================
// ==============================================================================================================
// ==============================================================================================================
// ==============================================================================================================



// ==============================================================================================================
// =============== All allowed types :
// ==============================================================================================================


class cNumber :
    public cPrimitiveType< double >
{
public:
    typedef cPrimitiveType< double > tSuperClass;


public:
    ~cNumber();
    cNumber( double iValue );

public:
    virtual  void SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument ) override;
    virtual  void LoadXML( tinyxml2::XMLElement* iNode ) override;
};

// ================
// ================
// ================

class cString :
    public cPrimitiveType< std::string >
{
public:
    typedef cPrimitiveType< std::string > tSuperClass;


public:
    ~cString();
    cString( const std::string& iValue );

public:
    virtual  void SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument ) override;
    virtual  void LoadXML( tinyxml2::XMLElement* iNode ) override;
};



// ==============================================================================================================
// ==============================================================================================================
// ==============================================================================================================


class cVariant
{
// The universal onion
public:
    union uAllTypes
    {
        // Constructor/Destructor
        ~uAllTypes() {};
        uAllTypes(){};

        uAllTypes& operator= ( const uAllTypes& iRHS )
        {
            if( this != &iRHS )
            {
                mNumber = iRHS.mNumber;
                mString = iRHS.mString;
            }
            return  *this;
        }

        // Values
        cNumber   mNumber;
        cString   mString;
    };

public:
    ~cVariant();
    cVariant();
    cVariant( eType iType );

public:
    eType       Type();

    double      GetValueNumber() const;
    std::string GetValueString() const;
    void        SetValueNumber( double iValue );
    void        SetValueString( std::string& iValue );

public:
    void SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument );
    void LoadXML( tinyxml2::XMLElement* iNode );

private:
    eType mType;
    uAllTypes   mValue;
};

} //nBase
