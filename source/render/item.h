//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// render/item.h Authored by Nathan Ross Powell
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#pragma once
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <functional>
#include "../types/int.hxx"
// Local includes.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
namespace render
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class Item
{
public:
    using PolyFunc = std::function<void()>;
// Variables
public:
protected:
private:
    static const PolyFunc sm_defaultFunc;
    U32 m_id;
// Functions
public:
    explicit Item( U32 id );
    bool operator == (const Item& rhs )
    {
        return this->m_id == rhs.m_id;
    }
    void setPolygons( PolyFunc func ){ m_polyFunc = func; }
    void resetPolygons() { m_polyFunc = sm_defaultFunc; }
    void drawPolygons() { m_polyFunc(); }
    auto getId() const { return m_id; };
protected:
private:
    PolyFunc m_polyFunc;
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// End namespace render.
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
