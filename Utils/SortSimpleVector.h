#ifndef UTILS_SORTSIMPLEVECTOR_H_
#define UTILS_SORTSIMPLEVECTOR_H_

#include <vector>
#include <algorithm>

template<typename T>
class SortSimpleVector
{
private:
    int _curMinIndex;
    int _curMaxIndex;
    std::vector<std::pair<T,int>> _indexes;
public:
    SortSimpleVector(std::vector<T>& data);
    
    //return -1 if empty
    int PopIndexMax();
    //return -1 if empty
    int PopIndexMin();

    bool Empty();
};

#include "SortSimpleVector.inl"


#endif //UTILS_SORTSIMPLEVECTOR_H_