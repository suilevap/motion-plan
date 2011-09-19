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
	for (int i = 0; i < _items.size(); ++i) 
	{
		delete[] _items[i];
	}
}

template<class T>
T* Pool<T>::Allocate()
{    
    T* result = NULL;
	int index;
	if (!_freeIds.empty())
	{
		result = _freeIds.top();
		_freeIds.pop();
	}
	else
	{
        if (_index < CHUNK_SIZE - 1)
        {
            Chunk chunk = *(_items.rbegin());
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
		_freeIds.push(obj);
		isSucceed = true;
//	}
	return isSucceed;
}

#endif
