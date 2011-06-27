#pragma once
#include <vector>
#include <stack>

template<class T>
class ObjectIdPool
{
private:
	std::vector<T*> _items;
	std::stack<int> _freeIds;
public:
	//ObjectIdPool(void);
	//~ObjectIdPool(void);

	//int New();
	//int Add(T* obj);
	//T* Get(int id);
	//bool Free(int id);
	ObjectIdPool(void)
	{
	}

	~ObjectIdPool(void)
	{
	}

	int New()
	{
		T* obj = new T();
		int index = Add(obj);
		return index;
	}


	int Add(T* obj)
	{
		int index;
		if (!_freeIds.empty())
		{
			index = _freeIds.top();
			_freeIds.pop();
			_items[index] = obj;
		}
		else
		{
			_items.push_back(obj);
			index = _items.size();
		}
		return index;
	}

	T* Get(int id)
	{
		T* result = NULL;
		if ((id>=0) &&(id<_items.size()))
		{
			result=_items[id];
		}
		return result;
	}

	bool Free(int id)
	{
		int isSucceed = false;
		if ((id>=0) &&(id<_items.size()))
		{
			if (_items[id] != NULL)
			{
				delete _items[id];
				_items[id] = NULL;
				_freeIds.push(id);
				isSucceed = true;
			}
		}
		return isSucceed;
	}


};

