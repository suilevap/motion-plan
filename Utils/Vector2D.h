#ifndef UTILS_VECTOR2D_H_
#define UTILS_VECTOR2D_H_

#include <vector>

template<typename T>
class Vector2D
{
private:

public:
    std::vector<T> Data;
    int Width;
    int Height;

    Vector2D(std::vector<T> data, int width);
    
    template<class Pr>
    bool CheckRegion(int x0, int y0, int x1, int y1, Pr predicate);

    void SetRegion(int x0, int y0, int x1, int y1, T val);

    inline int GetId(int x, int y);
    inline void GetXY(int id, int* x, int* y);

    bool On(int x, int y);

    template<class Pr>
    void FillRect(int x, int y, Pr predicate, int* x0, int* y0, int* x1, int* y1);


};

#include "Vector2D.inl"

#endif //UTILS_VECTOR2D_H_