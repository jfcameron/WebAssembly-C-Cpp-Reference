// © 2017 Joseph Cameron - All Rights Reserved
// Project: GDK
// Created on 17-07-03.
#include <gdk/vertexattribute.h>

#include <iostream>

using namespace GDK;
using namespace GFX;

std::ostream &GDK::GFX::operator<<(std::ostream &s, const GFX::VertexAttribute &a)
{
    s.clear(); s
    << "{"
    << "Name: " << a.name << ", "
    << "Size: " << a.size
    << "}";
    
    return s;
}

VertexAttribute::VertexAttribute(const std::string &aName, const unsigned short &aSize)
: name(aName)
, size(aSize)
{}
