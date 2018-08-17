// © 2018 Joseph Cameron - All Rights Reserved

#include <gdk/exception.h>

#include <iostream>

using namespace gdk;

std::ostream &gdk::operator<<(std::ostream &stream, const Exception &aException)
{
    stream.clear();
    stream << aException.what();
    return stream;
}
