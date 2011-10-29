#pragma once

#ifndef UTILS_MATHHELPER_H_
#define UTILS_MATHHELPER_H_

class MathHelper
{
public:
    static unsigned int UpperPowerOfTwo(unsigned int v);

    static unsigned int UpperRankOfTwo(unsigned int v);

    template<class T> 
    static inline T Clamp(T v, T lower, T upper) 
    {
        return v < lower ? lower : (v > upper ? upper : v); 
    }

};

#endif //UTILS_MATHHELPER_H_