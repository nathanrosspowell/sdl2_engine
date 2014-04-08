//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// command_line/base.h Authored by Nathan Ross Powell
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#pragma once

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Standard library.
#include <vector> 
#include <string>
#include <memory>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
namespace commandLine
{
    using Strings = std::vector< std::string >;
class IEntry
{
public:
    virtual ~IEntry(){}
    virtual std::string getCommandName() const = 0;
    virtual void dispatch( const Strings& arguments ) = 0;
};

class ScreenDimensions : public IEntry
{
private:
    int m_screenWidth = 800;
    int m_screenHeight = 400;
public:
    virtual ~ScreenDimensions(){}
    static std::string cmdName() { return "screenDimensions"; }
    virtual std::string getCommandName() const override { return cmdName(); }
    virtual void dispatch( const Strings& arguments ) override;
    int getScreenWidth() const { return m_screenWidth; }
    int getScreenHeight() const { return m_screenHeight; }
};

class AutoCloseTimer : public IEntry
{
private:
    int m_autoCloseTimer = 0;
public:
    virtual ~AutoCloseTimer(){}
    static std::string cmdName() { return "autoCloseTimer"; }
    virtual std::string getCommandName() const override { return cmdName(); }
    virtual void dispatch( const Strings& arguments ) override;
    bool hasSetAutoCloseTimer() const { return m_autoCloseTimer > 0; }
    int getAutoCloseTimer() const { return m_autoCloseTimer; }
};
  

    class Base
    {
    // Variables
    public:
    protected:
    private:
        std::vector< IEntry* > m_entries;
        int m_screenWidth;
        int m_screenHeight;
        int m_autoCloseTimer;
    // Functions
    public:
        explicit Base( const Strings& arguments );
        template < class T >
        const T& get() const
        {
            return static_cast< const T& >( find( T::cmdName() ) );
        }
    protected:
    private:
        void add( const std::string& name, IEntry* entry );
        void parse( const Strings& arguments );
        void dispatch( const std::string& name, const Strings& arguments );
        const IEntry& find( const std::string& name ) const;
        IEntry* find( const std::string& name );
    };
}