// © 2018 Joseph Cameron - All Rights Reserved
// Project: gdk
// Created on 2017-06-25.
#include <gdk/color.h>
//std inc
#include <iostream>

namespace gdk
{
    //static const
    const Color Color::Black      (0.0f,0.0f,0.0f,1.0f);
    const Color Color::White      (1.0f,1.0f,1.0f,1.0f);
    const Color Color::Red        (1.0f,0.0f,0.0f,1.0f);
    const Color Color::Green      (0.0f,1.0f,0.0f,1.0f);
    const Color Color::DarkGreen  (0.0f,0.6f,0.0f,1.0f);
    const Color Color::Blue       (0.0f,0.0f,1.0f,1.0f);
    const Color Color::DeathlyPink(1.0f,0.2f,0.8f,1.0f);

    const Color Color::CornflowerBlue(
        0.3921568627450980392156862745098,
        0.58431372549019607843137254901961,
        0.92941176470588235294117647058824,
        1.);

    //operators
    std::ostream &operator<< (std::ostream &s, const Color &a)
    {
        s.clear();
        
        s << "{"
          << "r: " << a.r << ", "
          << "g: " << a.g << ", "
          << "b: " << a.b << ", "
          << "a: " << a.a << "}";
    
        return s;
    }

    bool Color::operator==(const Color &aOther) const
    {
        return
            r == aOther.r &&
            g == aOther.g &&
            b == aOther.b &&
            a == aOther.a;
    }

    //ctors
    Color::Color()
        : r(0.)
        , g(0.)
        , b(0.)
        , a(1.)
    {}

    Color::Color(const float aR, const float aG, const float aB, const float aA)
        : r(aR)
        , g(aG)
        , b(aB)
        , a(aA)
    {}
}
