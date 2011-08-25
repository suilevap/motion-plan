#pragma once

#ifndef UTILS_SCALABLE_H_
#define UTILS_SCALABLE_H_

#include "Transformable.h"

template<class T>
class Scalable : public Transformable<T>
{
	double _scale;
public:
	Scalable(T* item, double scale);
	~Scalable(void);

	double TransformExact(double x);
};

#include "Scalable.inl"

#endif// UTILS_SCALABLE_H_

