#include <string>


enum eType
{
    kInvalid = 0,
    kNumber,
    kString
}

// Usefull for python essentially
template< typename T >
class cPrimitiveType
{

public:
    ~cPrimitiveType()
    cPrmitiveType( T& iValue );

public:
    T       GetValue() const;
    void    SetValue( const T& iValue );

public:
    void SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument );
    void LoadXML( tinyxml2::XMLElement* iNode );

protected:
    T mValue;
};


// ==============================================================================================================
// =============== All allowed types :
// ==============================================================================================================


typedef  cPrimitiveType< double >      cNumber;
typedef  cPrimitiveType< std::string > cString;



// ==============================================================================================================
// ==============================================================================================================
// ==============================================================================================================


class cVariant
{
// The universal onion
public:
    union uAllTypes
    {
        cNumber   mNumber;
        cString   mString;
    }

public:
    ~cVariant();
    cVariant();
    cVariant( eType iType );

public:
    eType       Type();
    uAllTypes&  Value();
    void        Value( uAllTypes& iValue );

public:
    void SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument );
    void LoadXML( tinyxml2::XMLElement* iNode );

private:
    const eType tType;
    uAllTypes mValue;
}
