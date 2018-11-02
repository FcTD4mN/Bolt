#pragma once


#include <string>


namespace nCore {
namespace nAI {


/*
    BlackBoardVariable is the base of any blackboard variables
*/

class cBlackBoardVariable
{
public:
    /** The destructor */
    ~cBlackBoardVariable();

    /** The constructor */
    cBlackBoardVariable();

    /** The constructor */
    cBlackBoardVariable( const  std::string&  iName );

public:
    /** Returns the variable name */
    const  std::string&  Name()  const;

    /** Sets the variable name */
    void  Name(const  std::string&  iName);

private:
    std::string  mName;
};


/** Template Variable for basic values */
template< typename T >
class cBlackBoardVariableT :
    public cBlackBoardVariable
{
public:
    /** The destructor */
    ~cBlackBoardVariableT();

    /** The constructor */
    cBlackBoardVariableT( const  T&  iValue );

public:
    /** Returns the Value of the variable */
    const  T&  Value() const;

    /** Sets the Value of the variable */
    void  Value( const  T&  iValue );

private:
    T  mValue;
};

template< typename T >
cBlackBoardVariableT< T >::~cBlackBoardVariableT()
{
}


template< typename T >
cBlackBoardVariableT< T >::cBlackBoardVariableT( const  T&  iValue) :
    cBlackBoardVariable(),
    mValue( iValue )
{

}

template< typename T >
const  T&
cBlackBoardVariableT< T >::Value()  const
{
    return  mValue;
}

template< typename T >
void
cBlackBoardVariableT< T >::Value( const  T&  iValue)
{
    mValue = iValue;
}


} // namespace nAI
} // namespace nCore

