#pragma once

#ifndef UTILS_TRANSFORMABLE_H_
#define UTILS_TRANSFORMABLE_H_

template<class T>
class Transformable
{
private: 
	T* _item;
public:
	Transformable(T* item);
	virtual ~Transformable(void);

	int Transform(double x);
	virtual double TransformExact(double x);


	T* GetItem();

};

#include "Transformable.inl"

#endif // UTILS_TRANSFORMABLE_H_

