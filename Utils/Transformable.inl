#ifndef UTILS_TRANSFORMABLE_H_
#error "Include from Transformable.h only."
#else

template<class T>
Transformable<T>::Transformable(T* item)
{
	_item = item;
}

template<class T>
Transformable<T>::~Transformable(void)
{
	delete _item;
}

template<class T>
int Transformable<T>:: Transform(double x) 
{
	return static_cast<int>(TransformExact(x));
}

template<class T>
double Transformable<T>:: TransformExact(double x) 
{
	return x;
}

template<class T>
inline T* Transformable<T>::GetItem()
{
	return _item;
}


#endif
