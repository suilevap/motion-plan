#ifndef UTILS_FASTVECTOR_H_
#define UTILS_FASTVECTOR_H_

template <typename T>
class FastVector
{
private:
    int index;
    std::vector<T> _data;
public:

    /*typedef std::vector<std::pair<int, float>>::iterator iter;
    iter current;*/

    FastVector()
    {
        index = 0;
        //current = _data.begin();
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

    inline void clear()
    {
        index = 0;
        //current = _data.begin();
    }

    inline void resize(int size)
    {
        _data.resize(size);
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

#endif//UTILS_FASTVECTOR_H_
