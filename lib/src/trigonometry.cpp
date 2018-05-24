// © 2017 Joseph Cameron - All Rights Reserved
// Project: GDK
// Created on 17-07-22.
#include "Trigonometry.h"
//std inc
#include <iostream>
#include <math.h>

using namespace GDK;
using namespace Math;

const double Trig::Double::PI = 4*::atan(1);
const float  Trig        ::PI = static_cast<float>(Trig::Double::PI);

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
