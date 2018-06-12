// © 2018 Joseph Cameron - All Rights Reserved

#include <gdk/trigonometry.h>

#include <cmath>
#include <iostream>

using namespace gdk;

const double trig::doubleprecision::PI = 4*::atan(1); //constexpr? Eval at cmake time?
const float  trig::PI = static_cast<float>(trig::doubleprecision::PI); //above

float trig::cos(const float a)
{
    return ::cosf(a);
}

float trig::sin(const float a)
{
    return ::sinf(a);
}

float trig::abs(const float a)
{
    return a < 0.? a*-1. : a;
}

double trig::doubleprecision::cos(const double a)
{
    return ::cos(a);
}

double trig::doubleprecision::sin(const double a)
{
    return ::sin(a);
}

double trig::doubleprecision::abs(const double a)
{
    return a < 0. ? a * -1. : a;
}
