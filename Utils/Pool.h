#pragma once

#ifndef UTILS_POOL_H_
#define UTILS_POOL_H_

#include <vector>
#include <stack>
#include "FastVector.h"


//Very simple pool implementation
//In future better use more efficient implementation(for example from boost)
template<class T>
class Pool
{
private:
    static const int CHUNK_INIT_SIZE = 32;
    typedef T* Chunk;
    int _index;
    int _chunkIndex;
    Chunk _currentChunk;

	std::vector<Chunk> _items;

	FastVector<T*, true> _freeItems;
    
    int AddChunk();
public:
	Pool();
	~Pool();
    
    T* Allocate();
    bool Free(T* obj);
    void Clear();
};

#include "Pool.inl"

#endif //UTILS_POOL_H_
