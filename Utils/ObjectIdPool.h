#pragma once

#ifndef UTILS_OBJECTIDPOOL_H_
#define UTILS_OBJECTIDPOOL_H_

#include <vector>
#include <stack>

template<class T>
class ObjectIdPool
{
private:
	std::vector<T*> _items;
	std::stack<int> _freeIds;
public:
	ObjectIdPool(void);
	~ObjectIdPool(void);

	int New();
	int Add(T* obj);
	T* Get(int id);
	bool Free(int id);
};

#include "ObjectIdPool.inl"

#endif //UTILS_OBJECTIDPOOL_H_
