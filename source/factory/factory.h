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
public:
    static void add( const std::string& classKey, Lambda factoryFunc );
    static void remove( const std::string& classKey );
    static ISetup* get( const std::string& classKey, JsonData jsonData );
};

}