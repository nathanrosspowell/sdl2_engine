//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// passport/base.h Authored by Nathan Ross Powell
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#pragma once
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "identity_factory.h"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
namespace passport
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
template< class T >
class Passport
{
    friend class IdentityFactory< T >;
// Variables
public:
protected:
private:
    typename T::IdentityType m_id;
// Functions
public:
    Passport();
    Passport( Passport< T >&& newId ) = default;
    Passport< T >& operator = ( Passport< T >&& rhs ) = default;
    bool operator == ( const Passport< T >& rhs ) const
    {
        return this->m_id == rhs.m_id;
    }
    const typename T::IdentityType& getIdentity() const
    {
        return m_id;
    } 
    bool isValid() const
    {
        return m_id != Passport< T >();
    }
protected:
private:
    explicit Passport( const typename T::IdentityType& newId );
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
template< class T >
Passport< T >::Passport()
: m_id( IdentityFactory< T >::getInvalidIdentity() ) 
{}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
template< class T >
Passport< T >::Passport( const typename T::IdentityType& newId )
: m_id( newId ) 
{}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
