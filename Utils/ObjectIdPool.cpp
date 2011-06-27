#include "StdAfx.h"
#include "ObjectIdPool.h"

//template<class T>
//ObjectIdPool<T>::ObjectIdPool(void)
//{
//}
//
//template<class T>
//ObjectIdPool<T>::~ObjectIdPool(void)
//{
//}
//
//template<class T>
//int ObjectIdPool<T>::New()
//{
//	T* obj = new T();
//	int index = Add(obj);
//	return index;
//}
//
//template<class T>
//int ObjectIdPool<T>::Add(T* obj)
//{
//	int index;
//	if (!_freeIds.empty())
//	{
//		index = _freeIds.top();
//		_freeIds.pop();
//		_items[index] = obj;
//	}
//	else
//	{
//		_items.push_back(obj);
//		index = _items.size();
//	}
//	return index;
//}
//
//template<class T>
//T* ObjectIdPool<T>::Get(int id)
//{
//	T* result = NULL;
	//if ((id>=0) &&(id<_items.size()))
	//{
	//	result=_items[id];
	//}
	//return result;
//}
//
//template<class T>
//bool ObjectIdPool<T>::Free(int id)
//{
//	int isSucceed = false;
//	if ((id>=0) &&(id<_items.size()))
//	{
//		if (_items[id] != NULL)
//		{
//			delete _items[id];
//			_items[id] = NULL;
//			_freeIds.push(id);
//			isSucceed = true;
//		}
//	}
//	return isSucceed;
//}
