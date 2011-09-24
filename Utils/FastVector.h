#ifndef UTILS_FASTVECTOR_H_
#define UTILS_FASTVECTOR_H_

template <typename T, bool AutoResize = false>
class FastVector
{
private:
    int index;
    std::vector<T> _data;
public:

    FastVector()
    {
        index = 0;
        if (AutoResize)
        {
            resize(4);
        }
    }

    inline void clear()
    {
        index = 0;
    }

    inline bool empty()
    {
        return (index == 0);
    }

    inline void resize(int size)
    {
        _data.resize(size);
    }

    inline int size()
    {
        return index;
    }

    inline void push_back(const T& item)
    {
        if (AutoResize)
        {
            if (index >= _data.size())
            {
                resize(_data.size()*2);
            }
        }
        _data[index++] = item;
    }

    inline T back()
    {
        return _data[index-1];
    }

    inline void pop_back()
    {
        index--;
    }

    inline T operator[](int i)
    {
        return _data[i];
    }

    inline void set(std::vector<T> values)
    {
        //TODO: check performance!!
        _data = values;
    }
};

#endif//UTILS_FASTVECTOR_H_
