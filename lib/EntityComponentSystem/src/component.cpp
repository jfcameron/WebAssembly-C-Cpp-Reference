// © 2017 Joseph Cameron - All Rights Reserved

#include <gdk/component.h>
#include <gdk/object.h>

#include <iostream>

static constexpr char TAG[] = "Component";

namespace gdk
{
    std::ostream &operator<<(std::ostream &s, const Component &a)
    {
        (void)a;
    
        s.clear(); s
        << "{"
        << TAG << "'s: " << "operator<< has not been implemented"
        // << "m_Member: " << a.m_Member << ", "
        << "}";
    
        return s;
    }

    std::weak_ptr<Object> Component::getObject() const
    {
        return m_Object;
    }
}
