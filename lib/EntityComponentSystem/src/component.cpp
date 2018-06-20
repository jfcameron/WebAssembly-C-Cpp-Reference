// © 2017 Joseph Cameron - All Rights Reserved

#include <gdk/component.h>
#include <gdk/gameobject.h>

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

    std::weak_ptr<GameObject> Component::getGameObject() const
    {
        return m_GameObject;
    }
}
