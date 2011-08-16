#pragma once

#ifndef MOTIONPLAN_MATHCONSTANTS_H_
#define MOTIONPLAN_MATHCONSTANTS_H_

#include "math.h"

//sqrt(2)
#define SQRT_2 1.41421356237309504880f
//sqrt(2*2 + 1*1)
#define SQRT_5 2.23606797749978969641

//sqrt(1*1 - 0.5 * 0.5)
//h in equilateral triangle
#define SQRT_075 0.86602540378443864676f

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif


#endif
