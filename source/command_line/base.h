//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// command_line/base.h Authored by Nathan Ross Powell
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#pragma once

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Standard library.
#include <vector> 
#include <string>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
namespace commandLine
{
    class Base
    {
    public:
        using Strings = std::vector< std::string >;
    // Variables
    public:
    protected:
    private:
        int m_screenWidth;
        int m_screenHeight;
        int m_autoCloseTimer;
    // Functions
    public:
        explicit Base( const Strings& arguments );
        int getScreenWidth() const { return m_screenWidth; }
        int getScreenHeight() const { return m_screenHeight; }
        bool hasSetAutoCloseTimer() const { return m_autoCloseTimer > 0; }
        int getAutoCloseTimer() const { return m_autoCloseTimer; }
    protected:
    private:
        void parse( const Strings& arguments );
        void dispatch( const std::string& name, const Strings& arguments );
        // 
        void setScreenDimensions( const Strings& arguments );
        void setAutoCloseTimer( const Strings& arguments );
    };
}