#pragma once

#ifndef UTILS_COMPARATORS_H_
#define UTILS_COMPARATORS_H_

#include <functional>

template<class T>
struct GreaterByRef
    : public std::binary_function<T*, T*, bool>
{	// functor for operator>
    bool operator()(const T* left, const T* right) const
	{	
        // apply operator> to operands
	    return (*left > *right);
	}
};

template<class T>
struct LessByRef
    : public std::binary_function<T*, T*, bool>
{	
    // functor for operator>
    bool operator()(const T* left, const T* right) const
	{	
        // apply operator> to operands
	    return (*left < *right);
	}
};

#endif //UTILS_COMPARATORS_H_