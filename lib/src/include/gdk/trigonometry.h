// © 2017 Joseph Cameron - All Rights Reserved
// Project: GDK
// Created on 17-07-22.
#ifndef GDK_MATH_TRIGONOMETRY_H
#define GDK_MATH_TRIGONOMETRY_H

namespace GDK
{
    namespace Math
    {
        /*!
         Trigonometry functions
         */
        namespace Trig
        {
            extern const float PI;
            
            float cos(const float);
            float sin(const float);
            float abs(const float);
            
            namespace Double
            {
                extern const double PI;
                
                double cos(const double);
                double sin(const double);
                double abs(const double);
            }
        }
    }
}

#endif /* GDK_MATH_TRIGONOMETRY_H  */
