// © 2018 Joseph Cameron - All Rights Reserved
// Project: gdk
// Created on 17-07-03.
#include <gdk/vertexattribute.h>

#include <iostream>

using namespace gdk;

std::ostream &gdk::operator<<(std::ostream &s, const VertexAttribute &a)
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
