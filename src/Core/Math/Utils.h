#pragma once

template< typename T >
T
RoundToClosestIntegerFactor( T iNumericValue, int iInteger )
{
    T  castIntegerValue = static_cast< T >( iInteger );
    return  round( iNumericValue / castIntegerValue ) * castIntegerValue;
}

template< typename T >
T
FloorToClosestIntegerFactor( T iNumericValue, int iInteger )
{
    T  castIntegerValue = static_cast< T >( iInteger );
    return  floor( iNumericValue / castIntegerValue ) * castIntegerValue;
}

//...