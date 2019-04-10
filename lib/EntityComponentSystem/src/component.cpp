// © 2017 Joseph Cameron - All Rights Reserved

#include <gdk/component.h>
#include <gdk/entity.h>

#include <nlohmann/json.hpp>

#include <iostream>

static constexpr char TAG[] = "Component";

namespace gdk
{
     std::ostream &Component::operator <<(std::ostream &s)
     {
        return s << nlohmann::json
        {
            {"Type", TAG}, 
            {"Debug Info", //This part is expensive. Should only be written if some symbol is defined etc. "Debug Info" should also be standardized.
                {}
            },
            
            {TAG, "UNIMPLEMENTED"},
        }
        .dump();
     }

    std::weak_ptr<Entity> Component::getEntity() const
    {
        return m_Entity;
    }


    std::string Component::toJSON()
    {
        return "{\"Type:\" \"Unimplemented!\"}";
    }
}

