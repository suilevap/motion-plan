#ifndef UTILS_SCALABLE_H_
#error "Include from Scalable.h only."
#else

template<class T>
Scalable<T>::Scalable(T* item, double scale)
:Transformable<T>(item)
{
	_scale = scale;
}

template<class T>
Scalable<T>::~Scalable(void)
{

}

template<class T>
double Scalable<T>::TransformExact(double x)
{ 
	return  x * _scale;
}

#endif
