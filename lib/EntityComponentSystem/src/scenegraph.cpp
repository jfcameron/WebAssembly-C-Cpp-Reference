// © 2017 Joseph Cameron - All Rights Reserved

#include <gdk/scenegraph.h>

#include <iostream>

namespace gdk
{
std::ostream& operator<<(std::ostream &s, const SceneGraph &a)
{
    (void)a;
    
    s.clear(); s
    << "{"
    << "SceneGraph's: " << "operator<< has not been implemented"
    // << "m_Member: " << a.m_Member << ", "
    << "}";
    
    return s;
}

SceneGraph::SceneGraph(Scene *a)
: m_MyScene(a)
{}
}
