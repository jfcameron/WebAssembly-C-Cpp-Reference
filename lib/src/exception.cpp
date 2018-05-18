// © 2017 Joseph Cameron - All Rights Reserved
// Project: GDK
// Created on 17-07-01.
#include "gdk/exception.h"
//std inc
#include <iostream>

using namespace gdk;

std::ostream &gdk::operator<<(std::ostream &stream, const Exception &aException)
{
    stream.clear();
    stream << aException.what();
    return stream;
}
