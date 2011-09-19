#pragma once

#ifndef UTILS_POOL_H_
#define UTILS_POOL_H_

#include <vector>
#include <stack>

//Very simple pool implementation
//In future better use more efficient implementation(for example from boost)
template<class T>
class Pool
{
private:
    static const int CHUNK_SIZE = 64;
    typedef T* Chunk;
    int _index;
	std::vector<Chunk> _items;

	std::stack<T*> _freeIds;
public:
	Pool();
	~Pool();
    
    T* Allocate();
    bool Free(T* obj);
};

#include "Pool.inl"

#endif //UTILS_POOL_H_
