#ifndef UTILS_SORTSIMPLEVECTOR_H_
#error "Include from SortSimpleVector.h only."
#else

template<typename T>
SortSimpleVector<T>::SortSimpleVector(std::vector<T>& data)
{
    int count = data.size();
    _curMinIndex = 0;
    _indexes.resize(count);
    _curMaxIndex = count-1;
    for (int i = 0; i < count; ++i)
    {
        _indexes[i]=std::pair<T,int>(data[i], i);
    }
    std::sort(_indexes.begin(), _indexes.end());
}

template<typename T>
int SortSimpleVector<T>::PopIndexMax()
{
    int result = -1;
    if (!Empty())
    {
        result = _indexes[_curMaxIndex].second;
        _curMaxIndex--;
    }
    return result;
}
template<typename T>
int SortSimpleVector<T>::PopIndexMin()
{
    int result = -1;
    if (!Empty())
    {
        result = _indexes[_curMinIndex].second;
        _curMinIndex++;
    }
    return result;
}

template<typename T>
bool SortSimpleVector<T>::Empty()
{
    return (_curMinIndex>_curMaxIndex);
}


#endif