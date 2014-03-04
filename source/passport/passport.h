//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// passport/base.h Authored by Nathan Ross Powell
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
namespace passport
{

template< class ISSUE >
class IdentityFactory
{
public:
using MyId = typename ISSUE::IdentityType;
// Variables
public:
    static const MyId sm_identityZero;
protected:
private:
    MyId m_identityCounter;
    // Functions
public:
    IdentityFactory() 
    : m_identityCounter( sm_identityZero ) 
    {}
    MyId getNewIdentity()
    {
        return m_identityCounter++;
    }
protected:
private:
};

template< class ISSUE >
const typename ISSUE::IdentityType IdentityFactory< ISSUE >::sm_identityZero = {};

template< class ISSUE >
class Passport
{
public:
using MyId = typename IdentityFactory< ISSUE >::MyId;
// Variables
public:
protected:
private:
    const MyId m_id;
// Functions
public:

    Passport();
    bool operator == ( const Passport< ISSUE >& rhs ) const
    {
        return this->m_id == rhs.m_id;
    }
protected:
private:
};

template< class ISSUE >
Passport< ISSUE >::Passport()
: m_id( IdentityFactory< ISSUE >::sm_identityZero ) 
{}

}