// © 2018 Joseph Cameron - All Rights Reserved
// Project: GDK
// Created on 17-07-22.
#include <gdk/trigonometry.h>

#include <iostream>
#include <cmath>

using namespace gdk;

const double Trig::Double::PI = 4*::atan(1); //constexpr? Eval at cmake time?
const float  Trig        ::PI = static_cast<float>(Trig::Double::PI); //above

float Trig::cos(const float a)
{
    return ::cosf(a);
}

float Trig::sin(const float a)
{
    return ::sinf(a);
}

float Trig::abs(const float a)
{
    return a < 0.? a*-1. : a;
}

double Trig::Double::cos(const double a)
{
    return ::cos(a);
}

double Trig::Double::sin(const double a)
{
    return ::sin(a);
}

double Trig::Double::abs(const double a)
{
    return a < 0. ? a * -1. : a;
}
