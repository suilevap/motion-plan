#ifndef UTILS_POOL_H_
#error "Include from Pool.h only."
#else

template<class T>
Pool<T>::Pool()
{
    Clear();
}

template<class T>
Pool<T>::~Pool()
{
    Clear();
    for (int i = 0; i < _items.size(); ++i) 
	{
		delete[] _items[i];
	}
    _items.clear();
}

template<class T>
void Pool<T>::Clear()
{
    _chunkIndex = 0;
    _freeItems.clear();
    _index = 0;
    if (_items.size()== 0)
    {
        _chunkIndex = AddChunk();
    }
    _currentChunk = _items[_chunkIndex];
}

//template<class T>
//T* Pool<T>::Allocate()
//{    
//    T* result = NULL;
//
//     //get next new object
//    if (_index < CHUNK_SIZE - 1)
//    {
//        Chunk chunk = _items[_chunkIndex];
//        result = &chunk[_index];
//        _index++;
//    }
//    else
//    if (!_freeItems.empty())
//    {
//        //get free object
//        result = _freeItems.back();
//        _freeItems.pop_back();
//    }
//    else
//    {
//        //chunk over
//        _chunkIndex++;
//        _index = 1;
//        Chunk chunk;
//        //create new chunk
//        if (_chunkIndex >= _items.size())
//        {
//            AddChunk();
//        }
//        chunk = _items[_chunkIndex];                
//        result = &chunk[0];    
//	}
//	return result;
//}

template<class T>
T* Pool<T>::Allocate()
{    
    T* result = NULL;
	if (!_freeItems.empty())
	{
        //get free object
        result = _freeItems.back();
        _freeItems.pop_back();
	}
	else
	{
         //get next new object
        if (_index < (CHUNK_INIT_SIZE<<_chunkIndex) - 1)
        {
            result = &(_currentChunk[_index]);
        }
        else
        {
            //chunk over
            _chunkIndex++;
            _index = 0;
            //create new chunk
            if (_chunkIndex >= _items.size())
            {
                AddChunk();
            }
            _currentChunk = _items[_chunkIndex];                
            result = _currentChunk;
        }
        _index++;

	}
	return result;
}


template<class T>
inline int Pool<T>::AddChunk()
{
    Chunk chunk = new T[CHUNK_INIT_SIZE<<_items.size()];
    _items.push_back(chunk);
    return _items.size() - 1;
}

template<class T>
bool Pool<T>::Free(T* obj)
{
	bool isSucceed = false;

    //TODO: fix issue with multiple free one object in pool
	_freeItems.push_back(obj);
	isSucceed = true;
	return isSucceed;
}

#endif
