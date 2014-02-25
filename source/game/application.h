//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// entity/base.h Authored by Nathan Ross Powell
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#pragma once
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Local.
#include "../command_line/base.h"


#include <functional>
#include <unordered_map>


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
namespace game
{

class IDataSetup;
using JsonData = void*;
using DataSetupLambda = std::function<IDataSetup*(JsonData)>;

class DataSetupFactorty
{
public:

    static std::unordered_map< std::string,DataSetupLambda > sm_map;

    static void add( const std::string& classKey, DataSetupLambda factoryFunc )
    {
        std::pair< std::string,DataSetupLambda > pair( classKey, factoryFunc );
        sm_map.insert( pair );
    }

    static void remove( const std::string& classKey )
    {
        sm_map.erase( classKey );
    }

    static IDataSetup* get( const std::string& classKey, JsonData jsonData )
    {
        auto newSetup = sm_map[ classKey ]( jsonData );
        return newSetup;
    }
};

class IDataSetup
{
public:
    virtual void DataSetup( JsonData json ) = 0;
};

class DataClass : public IDataSetup
{
    public:
    DataClass( JsonData json )
    {}
    virtual void DataSetup( JsonData json ) override
    {
        
    }
};

class DataSetupRegister
{
private:
    const std::string m_classKey;
public:
    DataSetupRegister( const std::string& classKey, DataSetupLambda factoryFunc )
    : m_classKey( classKey )
    {
        DataSetupFactorty::add( m_classKey, factoryFunc );
    }
    ~DataSetupRegister()
    {
        DataSetupFactorty::remove( m_classKey );
    }
};


class Application
{
public:
    enum class State
    {
        Created,
        Loading,
        Running,
        ShuttingDown,
        Finished,
    };
protected:
private:
// Variables
public:
protected:
private:
    const commandLine::Base m_cmdLine;
    State m_state;
// Functions
public:
     explicit Application( const commandLine::Base& arguments );
     void update();
protected:
private:
    void startUp();
    void shutDown();
    bool finishedLoading();
    void running();
    bool finishedShuttingDown();
};

}