// © 2018 Joseph Cameron - All Rights Reserved

#include <gdk/glh.h>
#include <gdk/nlohmann_json_util.h>
#include <gdk/opengl.h>
#include <gdk/vector2.h>
#include <gdk/vector2uniformcollection.h>

#include <nlohmann/json.hpp>

#include <iostream>

using namespace gdk;

static constexpr char TAG[] = "Vector2UniformCollection";

std::ostream &gdk::operator<<(std::ostream &s, const Vector2UniformCollection &a)
{
    nlohmann::json root = 
    {
        {"Type", TAG}, 
        {"Debug Info", //This part is expensive. Should only be written if some symbol is defined etc. "Debug Info" should also be standardized.
            {}
        },
    };

    for (auto &pair : a.m_Map) root[pair.first] = jfc::insertion_operator_to_nlohmann_json_object(pair.second.get());

    return s << root.dump();
}

void Vector2UniformCollection::bind(const GLuint aProgramHandle) const
{
    for (auto &pair : m_Map) glh::Bind2FloatUniform(aProgramHandle, pair.first, *pair.second.get());
}

void Vector2UniformCollection::unbind(const GLuint aProgramHandle) const
{
    for (auto &pair : m_Map) glh::Bind2FloatUniform(aProgramHandle, pair.first, Vector2::Zero);
}
