//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// entity/base.h Authored by Nathan Ross Powell
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#pragma once
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <functional>
#include <unordered_map>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
namespace factory
{

class ISetup;
using JsonData = void*;
using Lambda = std::function<ISetup*(JsonData)>;

class Factory
{
public:

    static std::unordered_map< std::string,Lambda > sm_map;

    static void add( const std::string& classKey, Lambda factoryFunc );
    static void remove( const std::string& classKey );
    static ISetup* get( const std::string& classKey, JsonData jsonData );
};

class ISetup
{
public:
    virtual void doSetup( JsonData json ) = 0;
};

class DataClass : public ISetup
{
    public:
    DataClass( JsonData json )
    {}
    virtual void doSetup( JsonData json ) override
    {
        
    }
};

class Register
{
private:
    const std::string m_classKey;
public:
    Register( const std::string& classKey, Lambda factoryFunc )
    : m_classKey( classKey )
    {
        Factory::add( m_classKey, factoryFunc );
    }
    ~Register()
    {
        Factory::remove( m_classKey );
    }
};

}