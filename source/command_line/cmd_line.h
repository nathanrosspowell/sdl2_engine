//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// command_line/cmd_line.h Authored by Nathan Ross Powell
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#pragma once
#include "i_entry.h"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Standard library.
#include <memory>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
namespace commandLine
{
class CmdLine
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
    explicit CmdLine( const Strings& arguments );
    ~CmdLine();
    template < class T >
    const T& get() const
    {
        return static_cast< const T& >( find( T::cmdName() ) );
    }
protected:
private:
    void parse( const Strings& arguments );
    void dispatch( const std::string& name, const Strings& arguments );
    const IEntry& find( const std::string& name ) const;
    IEntry* find( const std::string& name );
};
}