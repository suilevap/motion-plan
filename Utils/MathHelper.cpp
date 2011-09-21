#include "StdAfx.h"

#include "MathHelper.h"

unsigned int MathHelper::UpperPowerOfTwo(unsigned int v)
{
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;
    return v;
}

unsigned int MathHelper::UpperRankOfTwo(unsigned int v)
{
    //unsigned int v;  // 32-bit value to find the log2 of 
    const unsigned int b[] = {0x2, 0xC, 0xF0, 0xFF00, 0xFFFF0000};
    const unsigned int S[] = {1, 2, 4, 8, 16};
    int i;

    register unsigned int r = 0; // result of log2(v) will go here
    for (i = 4; i >= 0; i--) // unroll for speed...
    {
      if (v & b[i])
      {
        v >>= S[i];
        r |= S[i];
      } 
    }
    r++;
    return r;
}
