// © 2018 Joseph Cameron - All Rights Reserved

#ifndef GDK_MATH_TRIGONOMETRY_H
#define GDK_MATH_TRIGONOMETRY_H

namespace gdk
{
    //! Trigonometry functions
    namespace trig
    {
        extern const float PI;
            
        float cos(const float);
        float sin(const float);
        float abs(const float);
            
        namespace doubleprecision
        {
            extern const double PI;
                
            double cos(const double);
            double sin(const double);
            double abs(const double);
        }
    }
}

#endif
