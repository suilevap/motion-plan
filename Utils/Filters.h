#pragma once

#ifndef UTILS_FILTERS_H_
#define UTILS_FILTERS_H_

#include <functional>

template<class T, T V>
struct FilterNEQ
    : public std::unary_function<T,bool>
{	// functor for operator>
    bool operator()(const T val) const
	{	
        // apply operator> to operands
	    return (val != V);
	}
};



#endif //UTILS_FILTERS_H_