// © 2018 Joseph Cameron - All Rights Reserved

#include <gdk/glh.h>
#include <gdk/mat4x4uniformcollection.h>
#include <gdk/nlohmann_json_util.h>
#include <gdk/opengl.h>

#include <nlohmann/json.hpp>

#include <iostream>

namespace gdk
{
std::ostream &operator<<(std::ostream &s, const Mat4x4UniformCollection &a)
{
    nlohmann::json root;

    for (auto &pair : a.m_Map) root[pair.first] = jfc::insertion_operator_to_nlohmann_json_object(pair.second);

    return s << root.dump();
}

void Mat4x4UniformCollection::bind(const GLuint aProgramHandle) const
{
    for (auto &pair : m_Map) glh::BindMatrix4x4(aProgramHandle, pair.first, pair.second);
}

void Mat4x4UniformCollection::unbind(const GLuint aProgramHandle) const
{
    for (auto &pair : m_Map) glh::BindMatrix4x4(aProgramHandle, pair.first, Mat4x4::Identity);    
}
}
