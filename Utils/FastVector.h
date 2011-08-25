#ifndef UTILS_FASTVECTOR_H_
#define UTILS_FASTVECTOR_H_

template <typename T>
class FastVector
{
private:
    int index;
    std::vector<T> _data;
public:

    FastVector()
    {
        index = 0;
    }

    inline void clear()
    {
        index = 0;
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
        _data[index++] = item;

    }
    inline T operator[](int i)
    {
        return _data[i];
    }
};

#endif//UTILS_FASTVECTOR_H_
