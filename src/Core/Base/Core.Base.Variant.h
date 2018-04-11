#include <tinyxml2.h>


#include <string>


namespace nBase {


enum eType
{
    kInvalid = 0,
    kNumber,
    kString
};

class cVariant
{
public:
    ~cVariant();
    cVariant();

public:
    // Makers
    static cVariant* MakeVariant( eType iType );
    static cVariant* MakeVariant( double iNumber );
    static cVariant* MakeVariant( const std::string& iString );

public:
    virtual  eType  Type();

    double      GetValueNumber() const;
    std::string GetValueString() const;
    void        SetValueNumber( double iValue );
    void        SetValueString( std::string& iValue );

public:
    virtual  void SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument );
    virtual  void LoadXML( tinyxml2::XMLElement* iNode );
    static  cVariant* MakeFromXML( tinyxml2::XMLElement* iNode );
};



// ==============================================================================================================
// =============== All allowed types :
// ==============================================================================================================


class cNumber :
    public cVariant
{
public:
    typedef cVariant tSuperClass;


public:
    ~cNumber();
    cNumber( double iValue );

public:
    double Value() const;
    void Value( double iValue );

public:
    virtual  void SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument ) override;
    virtual  void LoadXML( tinyxml2::XMLElement* iNode ) override;

protected:
    double  mValue;
};


// ================
// ================
// ================


class cString :
    public cVariant
{
public:
    typedef cVariant tSuperClass;


public:
    ~cString();
    cString( const std::string& iValue );
    cString( const cString& iRHS );

public:
    const std::string& Value() const;
    void Value( const std::string& iValue );

public:
    virtual  void SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument ) override;
    virtual  void LoadXML( tinyxml2::XMLElement* iNode ) override;

protected:
    std::string  mValue;
};


} // namespace nBase

