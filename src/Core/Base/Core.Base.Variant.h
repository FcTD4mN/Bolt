#pragma once

#include <tinyxml2.h>


#include <string>
#include <functional>


namespace nCore {
namespace nBase {


enum eType
{
    kInvalid = 0,
    kNumber,
    kString,
    kBoolean
};

enum eVariableState
{
    kBeforeChange,
    kAfterChange
};


class cVariant
{
public:
    virtual ~cVariant() = 0;
    cVariant();
    cVariant( const cVariant& iRHS );

public:
    // Makers
    static cVariant* MakeVariant( eType iType );
    static cVariant* MakeVariant( double iNumber );
    static cVariant* MakeVariant( int iNumber );
    static cVariant* MakeVariant( const std::string& iString );
    static cVariant* MakeVariant( bool iBoolean );
    virtual  cVariant* Clone() = 0;

public:
    // Access
    virtual  eType                  Type() const;
    virtual  std::string            TypeAsString() const;

    virtual  double                 GetValueNumber() const;
    virtual  const std::string&     GetValueString() const;
    virtual  bool                   GetValueBool() const;
    virtual  void                   SetValueNumber( double iValue );
    virtual  void                   SetValueString( const std::string& iValue );
    virtual  void                   SetValueBool( bool iValue );

    virtual  std::string            ToString() const = 0;

    void                            SetValueChangeCallback( std::function< void( eVariableState ) > iFunction );

public:
    virtual  void SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument );
    virtual  void LoadXML( tinyxml2::XMLElement* iNode );
    static  cVariant* MakeFromXML( tinyxml2::XMLElement* iNode );

public:
    virtual  cVariant& operator= ( const cVariant& iRHS ) = 0;

protected:
    std::vector< std::function< void( eVariableState ) > > mValueChangeCallback;
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
    cNumber( const cNumber& iRHS );

public:
    // Makers
    virtual  cNumber*  Clone() override;

public:
    // Access
    double Value() const;
    void Value( double iValue );

    virtual  eType  Type() const override;
    virtual  std::string TypeAsString() const override;

public:
    virtual  std::string  ToString() const  override;

public:
    virtual  void SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument ) override;
    virtual  void LoadXML( tinyxml2::XMLElement* iNode ) override;

public:
    virtual  cVariant& operator= ( const cVariant& iRHS ) override;

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
    // Makers
    virtual  cString*  Clone() override;

public:
    // Access
    const std::string& Value() const;
    void Value( const std::string& iValue );

    virtual  eType  Type() const override;
    virtual  std::string TypeAsString() const override;

public:
    virtual  std::string  ToString()  const  override;

public:
    virtual  void SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument ) override;
    virtual  void LoadXML( tinyxml2::XMLElement* iNode ) override;

public:
    virtual  cVariant& operator= ( const cVariant& iRHS ) override;

protected:
    std::string  mValue;
};


// ================
// ================
// ================


class cBoolean :
    public cVariant
{
public:
    typedef cVariant tSuperClass;


public:
    ~cBoolean();
    cBoolean( bool iValue );
    cBoolean( const cBoolean& iRHS );

public:
    // Makers
    virtual  cBoolean*  Clone() override;

public:
    // Access
    bool Value() const;
    void Value( bool iValue );

    virtual  eType  Type() const override;
    virtual  std::string TypeAsString() const override;

public:
    virtual  std::string  ToString()  const  override;

public:
    virtual  void SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument ) override;
    virtual  void LoadXML( tinyxml2::XMLElement* iNode ) override;

public:
    virtual  cVariant& operator= ( const cVariant& iRHS ) override;

protected:
    bool  mValue;
};


} // namespace nBase
} // namespace nCore

