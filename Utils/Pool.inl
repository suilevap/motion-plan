#ifndef UTILS_POOL_H_
#error "Include from Pool.h only."
#else

template<class T>
Pool<T>::Pool()
{
    _index = CHUNK_SIZE;
}

template<class T>
Pool<T>::~Pool()
{
    Clear();
}

template<class T>
void Pool<T>::Clear()
{
	for (int i = 0; i < _items.size(); ++i) 
	{
		delete[] _items[i];
	}
    _items.clear();
    _freeItems.clear();
    _index = CHUNK_SIZE;
}

template<class T>
T* Pool<T>::Allocate()
{    
    T* result = NULL;
	int index;
	if (!_freeItems.empty())
	{
        result = _freeItems.back();
        _freeItems.pop_back();
	}
	else
	{
        if (_index < CHUNK_SIZE - 1)
        {
            Chunk chunk = _items.back();
            result = &chunk[_index];
        }
        else
        {
            _index = 0;
            Chunk chunk = new T[CHUNK_SIZE];
            _items.push_back(chunk);
            result = &chunk[0];
        }
        _index++;

	}
	return result;
}

template<class T>
bool Pool<T>::Free(T* obj)
{
	bool isSucceed = false;
 //   int id = (obj-_items.begin())/(sizeof(*obj))
	//if ((id>=0) &&(id<_items.size()))
	//{
        //TODO: fix issue with multiple free one object in pool
		_freeItems.push_back(obj);
		isSucceed = true;
//	}
	return isSucceed;
}

#endif
