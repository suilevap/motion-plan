// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <stack>

#include <time.h>

#include <Interface.h>
#include <FileStruct.h>

//
//int _tmain(int argc, _TCHAR* argv[])
//{
//
//	clock_t time0, time1, times;
//	//FileStruct f("map2.txt");
//
//	//char * result = Action(f.GetBuffer());
//	//printf(result);
//	TestPerformance(true);
//	//TestSparsePerformance(true);
//	times = clock();
//	time0 = times;
//	for (int i=1; i < 100000; i++)
//	{
//		TestPerformance(false);
//		//TestSparsePerformance(false);
//		if (i%1000 == 0)
//		{
//			time1 = clock();
//			printf("%3dk time: %4d, avg time: %4d\n",i/1000, (time1 - time0), (time1 - times)/(i/1000) );
//			time0 = time1;
//		}
//	}
//	getchar();	
//	return 0;
//}


void Test1()
{
    static std::vector<std::pair<int,float>> data;
    static float sum = 0;
    data.clear();
    data.push_back(std::pair<int,float>(1,0.1));
    data.push_back(std::pair<int,float>(1,0.1));
    data.push_back(std::pair<int,float>(1,0.1));
    data.push_back(std::pair<int,float>(1,0.1));
    data.push_back(std::pair<int,float>(1,0.1));
    data.push_back(std::pair<int,float>(1,0.1));
    data.push_back(std::pair<int,float>(1,0.1));
    data.push_back(std::pair<int,float>(1,0.1));

    //for (std::vector<std::pair<int,float>>::const_iterator it = data.begin(); it != data.end(); ++it)
    //{
    //    //std::pair<int,float> p = *it;
    //    //sum += p.first + p.second;
    //    sum += it->first + it->second;
    //}

    int count = data.size();
    for (int i=0; i < count; ++i)
    {
        std::pair<int,float>& p = data[i];
        sum += p.first + p.second;
    }
}

void Test2()
{
    static std::vector<std::pair<int,float>> data;
    static float sum = 0;
    
    data.resize(8);
    int i = 0;
    data[i++] = (std::pair<int,float>(1,0.1));
    data[i++] = (std::pair<int,float>(1,0.1));
    data[i++] = (std::pair<int,float>(1,0.1));
    data[i++] = (std::pair<int,float>(1,0.1));
    data[i++] = (std::pair<int,float>(1,0.1));
    data[i++] = (std::pair<int,float>(1,0.1));
    data[i++] = (std::pair<int,float>(1,0.1));
    data[i++] = (std::pair<int,float>(1,0.1));
    int count = i;

    for (int i=0; i < count; ++i)
    {
        std::pair<int,float>& p = data[i];
        sum += p.first + p.second;
    }
}

template <typename T>
class MyVector
{
public:
    int index;
    std::vector<T> _data;

    typedef std::vector<std::pair<int, float>>::iterator iter;
    iter current;

    MyVector()
    {
        index = 0;
        current = _data.begin();
    }

    //inline iter begin()
    //{
    //    return _data.begin();
    //}

    //inline T front()
    //{
    //    return _data.front();
    //}

    //inline iter end()
    //{
    //    return (current);
    //}

    inline void clear(int s)
    {
        index = 0;
        _data.resize(s);
        current = _data.begin();
    }

    inline int size()
    {
        return index;
        //return current-_data.begin();
    }

    inline void push_back(const T& item)
    {
        //if (index < _data.size())
        //{
        //    _data[index] = item;
        //}
        //else
        //{
        //    _data.push_back(item);
        //}
        //*current = item;
        //++current;
        //index++;
        _data[index++] = item;

    }
    inline T operator[](int i)
    {
        return _data[i];
    }
};

void Test3()
{
    static MyVector<std::pair<int,float>> data;
    static float sum = 0;
    data.clear(10);
    data.push_back(std::pair<int,float>(1,0.1));
    data.push_back(std::pair<int,float>(1,0.1));
    data.push_back(std::pair<int,float>(1,0.1));
    data.push_back(std::pair<int,float>(1,0.1));
    data.push_back(std::pair<int,float>(1,0.1));
    data.push_back(std::pair<int,float>(1,0.1));
    data.push_back(std::pair<int,float>(1,0.1));
    data.push_back(std::pair<int,float>(1,0.1));

    //std::vector<std::pair<int,float>>::const_iterator& end = data.end();
    //for (std::vector<std::pair<int,float>>::const_iterator it = data.begin(); 
    //    it != end; ++it)
    //{
    //    std::pair<int,float> p = *it;
    //    sum += p.first + p.second;
    //    //sum += it->first + it->second;
    //}

    int count = data.size();
    for (int i=0; i < count; ++i)
    {
        std::pair<int,float>& p = data[i];
        sum += p.first + p.second;
    }
    //const int num = data.index;
    //const std::pair<int,float>* ptr = (num != 0) ? &data.front() : NULL;
    //for(int i = 0; i < num; i++)
    //{
    //    std::pair<int,float> p = ptr[i];
    //    sum += p.first + p.second;
    //}
}

int _tmain(int argc, _TCHAR* argv[])
{

	clock_t time0, time1, times;

	times = clock();
	time0 = times;
	for (int i=1; i < 100000000; i++)
	{
		Test1();
		//TestSparsePerformance(false);
		if (i%1000000 == 0)
		{
			time1 = clock();
			printf("%3dk time: %4d, avg time: %4d\n",i/1000000, (time1 - time0), (time1 - times)/(i/1000000) );
			time0 = time1;
		}
	}
	getchar();	
	return 0;
}

