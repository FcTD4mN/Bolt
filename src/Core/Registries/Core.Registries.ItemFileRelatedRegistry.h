#pragma once


#include <unordered_map>
#include <functional>


#include "Core.Base.FileSystem.h"

namespace nCore {
namespace nBase {


/*
    This class links a string, that works like an ID, to a set of datas ( an item and its file )
    This version is nice if we need to access a lot of item in a fast manner.
    Not so if we need to change item's name/id, as we need to keep the string up to date, which is tedious to do.
    For example when editing entities/components/systems name in editor, we need to unregister old name, and register the new one ...
*/
template< class T >
class cItemFileRelatedRegistry
{
public:
    struct sPairItemFile
    {
        sPairItemFile() : mItem( 0 ), mFile( "" ){}

        T                       mItem;
        nStdFileSystem::path    mFile;
    };

public:
    // Contruction/Destruction
    virtual  ~cItemFileRelatedRegistry();
    cItemFileRelatedRegistry();

public:
    // Init/Finalize
    virtual  void  Initialize();
    virtual  void  Finalize();

public:
    // Registry functions
    void    RegisterItem( const std::string& iName, T iItem );
    void    RegisterItem( const std::string& iName, T iItem, const nStdFileSystem::path& iPath );
    void    UnregisterItem( T iItem );
    void    UnregisterItemByName( const std::string& iName );
    const T GetItemByName( const std::string& iName );

    bool    IsItemNameAlreadyInRegistry( const std::string& iName ) const;

    const T                     GetItemAssociatedToFile( const nStdFileSystem::path& iFile );
    nStdFileSystem::path        GetItemFileByItemName( const std::string& iName );
    nStdFileSystem::path        GetItemFileByItem( const T iItem );
    void                        SetItemFileUsingItem( const T iItem, const nStdFileSystem::path& iNewFile );
    void                        SetItemFileUsingItemName( const std::string& iItemName, const nStdFileSystem::path& iNewFile );

public:
    // EDITOR
    int                         ItemCount();
    T                           GetItemAtIndex( int iIndex );
    std::vector< std::string >  GetItemNamesSorted();


protected:
    std::unordered_map< std::string, sPairItemFile >    mItems;

};


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Construction
// -------------------------------------------------------------------------------------


template< class T >
cItemFileRelatedRegistry< T >::~cItemFileRelatedRegistry()
{
}


template< class T >
cItemFileRelatedRegistry< T >::cItemFileRelatedRegistry()
{
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------- Init/Finalize
// -------------------------------------------------------------------------------------


template< class T >
void
cItemFileRelatedRegistry< T >::Initialize()
{
}


template< class T >
void
cItemFileRelatedRegistry< T >::Finalize()
{
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------ Registry functions
// -------------------------------------------------------------------------------------


template< class T >
void
cItemFileRelatedRegistry< T >::RegisterItem( const std::string& iName, T iItem )
{
    mItems[ iName ].mItem = iItem;
    mItems[ iName ].mFile = "";
}


template< class T >
void
cItemFileRelatedRegistry< T >::RegisterItem( const std::string& iName, T iItem, const nStdFileSystem::path& iPath )
{
    mItems[ iName ].mItem = iItem;
    mItems[ iName ].mFile = iPath;
}


template< class T >
void
cItemFileRelatedRegistry< T >::UnregisterItem( T iItem )
{
    for( int i = 0; i < mItems.size(); ++i )
        if( mItems[ i ].second.mItem == iItem )
            mItems.erase( mItems.begin() + i );
}


template< class T >
void
cItemFileRelatedRegistry< T >::UnregisterItemByName( const std::string& iName )
{
    mItems.erase( iName );
}


template< class T >
const T
cItemFileRelatedRegistry< T >::GetItemByName( const std::string& iName )
{
    if( !IsItemNameAlreadyInRegistry( iName ) )
        return  0;

    return  mItems[ iName ].mItem;
}


template< class T >
bool
cItemFileRelatedRegistry< T >::IsItemNameAlreadyInRegistry( const std::string& iName ) const
{
    auto it = mItems.find( iName );
    if( it != mItems.end() )
        return  true;

    return  false;
}


template< class T >
const T
cItemFileRelatedRegistry< T >::GetItemAssociatedToFile( const nStdFileSystem::path& iFile )
{
    for( auto item : mItems )
    {
        if( item.second.mFile.empty() )
            continue;

        if( item.second.mFile == iFile )
            return  item.second.mItem;
    }

    return  0;
}


template< class T >
nStdFileSystem::path
cItemFileRelatedRegistry< T >::GetItemFileByItemName( const std::string & iName )
{
    if( !IsItemNameAlreadyInRegistry( iName ) )
        return  "";

    return  mItems[ iName ].mFile;
}


template<class T>
nStdFileSystem::path
cItemFileRelatedRegistry<T>::GetItemFileByItem( const T iItem )
{
    // & is mandatory otherwise it'll copy items
    for( auto& item : mItems )
    {
        if( item.second.mItem == iItem )
            return  item.second.mFile;
    }

    return nStdFileSystem::path();
}

template<class T>
void
cItemFileRelatedRegistry<T>::SetItemFileUsingItem( const T iItem, const nStdFileSystem::path & iNewFile )
{
    // & is mandatory otherwise it'll copy items
    for( auto& item : mItems )
    {
        if( item.second.mItem == iItem )
            item.second.mFile = iNewFile;
    }
}


template< class T >
void
cItemFileRelatedRegistry< T >::SetItemFileUsingItemName( const std::string & iItemName, const nStdFileSystem::path& iNewFile )
{
    if( !IsItemNameAlreadyInRegistry( iItemName ) )
        return;

    mItems[ iItemName ].mFile = iNewFile;
}


template< class T >
int
cItemFileRelatedRegistry< T >::ItemCount()
{
    return  int(mItems.size());
}


template< class T >
T
cItemFileRelatedRegistry< T >::GetItemAtIndex( int iIndex )
{
    // Can we do this better than a for loop like this ? like accessing index in unordered map ? even though it's not working like that
    auto iterator = mItems.begin();
    for( int i = 0; i < iIndex; ++i )
        ++iterator;

    return  iterator->second.mItem;
}


template< class T >
std::vector<std::string>
cItemFileRelatedRegistry< T >::GetItemNamesSorted()
{
    std::vector< std::string > output;
    output.reserve( mItems.size() );

    for( auto item : mItems )
    {
        if( item.second.mItem )
            output.push_back( item.first );
    }

    std::sort( output.begin(), output.end() );

    return  output;
}


} // namespace nBase
} // namespace nCore

