#ifndef UTILS_VECTOR2D_H_
#error "Include from Vector2D.h only."
#else

template<typename T>
Vector2D<T>::Vector2D(std::vector<T> data, int width)
{
    Data = data;
    Width = width;
    Height = Data.size() / Width;
}

template<typename T>
Vector2D<T>::Vector2D(int width, int height)
{
    Width = width;
    Height = height;
    Data.resize(Width * Height);
}

template<typename T>
bool Vector2D<T>::On(int x, int y)
{
    return (x >= 0 && x < Width && y >= 0 && y < Height);
}

template<typename T>
template<class Pr>
bool Vector2D<T>::CheckRegion(int x0, int y0, int x1, int y1, Pr predicate)
{
    //TODO: fix several return

    if (!On(x0,y0) || !On(x1, y1))
    {
        return false;
    }
    for (int x = x0; x <= x1; ++x)
    {
        for (int y = y0; y <= y1; ++y)
        {
            int id = GetId(x,y);
            if (!predicate(Data[id]))
            {
                return false;
            }
        }
    }
    return true;
}

template<typename T>
template<class Pr>
void Vector2D<T>::Blur(float a, Pr predicate)
{
    float ra = 1 - a;
    for (int x = 0; x < Width; ++x)
    {
        for (int y = 0; y < Height; ++y)
        {
            T value = GetData(x,y);
            if (predicate(value))
            {
                T sum = GetDataSafe(x-1, y-1) + GetDataSafe(x, y-1) + GetDataSafe(x+1, y-1) +
                    GetDataSafe(x-1, y) + GetDataSafe(x+1, y) +
                    GetDataSafe(x-1, y+1) + GetDataSafe(x, y+1) + GetDataSafe(x+1, y+1);
                value = a * value + ra * sum / 8;
                SetData(x, y, value);
            }
        }
    }
}

template<typename T>
void Vector2D<T>::SetRegion(int x0, int y0, int x1, int y1, T val)
{
    for (int x = x0; x <= x1; ++x)
    {
        for (int y = y0; y <= y1; ++y)
        {
            int id = GetId(x,y);
            Data[id] = val;
        }
    }
}

template<typename T>
int Vector2D<T>::GetId(int x, int y)
{
    return x + y * Width;
}
template<typename T>
int Vector2D<T>::GetIdSafe(int x, int y)
{
    x = MathHelper::Clamp(x, 0, Width-1);
    y = MathHelper::Clamp(y, 0, Height-1);
    return x + y * Width;
}
template<typename T>
void Vector2D<T>::GetXY(int id, int* x, int* y)
{
    *x = id % Width;
    *y = id / Width;
}
template<typename T>
T Vector2D<T>::GetData(int x, int y)
{
    return Data[GetId(x, y)];
}
template<typename T>
void Vector2D<T>::SetData(int x, int y, T value)
{
    Data[GetId(x, y)] = value;
}
template<typename T>
T Vector2D<T>::GetDataSafe(int x, int y)
{
    return Data[GetIdSafe(x, y)];
}
template<typename T>
void Vector2D<T>::SetDataSafe(int x, int y, T value)
{
    Data[GetIdSafe(x, y)] = value;
}

template<typename T>
template<class Pr>
void Vector2D<T>::FillRect(int x, int y, Pr predicate, int* px0, int* py0, int* px1, int* py1)
{
    int x0 = x;
    int y0 = y;
    int x1 = x;
    int y1 = y;
    bool x0free = true;
    bool y0free = true;
    bool x1free = true;
    bool y1free = true;
    //(x0,y0) (x1,y0)
    //(x0,y1) (x1,y1)
    //expand
    do
    {        
        //(x0,y0)*(x1,y0)
        //(x0,y1)*(x1,y1)
        if (x0free)
        {
            x0free = CheckRegion(x0-1, y0, x0-1, y1, predicate);
            if (x0free)
            {
                x0--;
            }
        }
        
        //(x0,y0)*(x1,y0)*
        //(x0,y1) (x1,y1)
        if (y0free)
        {
            y0free = CheckRegion(x0, y0-1, x1, y0-1, predicate);
            if (y0free)
            {
                y0--;
            }
        }
        //(x0,y0) (x1,y0)*
        //(x0,y1) (x1,y1)*
        if (x1free)
        {
            x1free = CheckRegion(x1+1, y0, x1+1, y1, predicate);
            if (x1free)
            {
                x1++;
            }
        }
        //(x0,y0) (x1,y0)
        //(x0,y1)*(x1,y1)*
        if (y1free)
        {
            y1free = CheckRegion(x0, y1+1, x1, y1+1, predicate);
            if (y1free)
            {
                y1++;
            }
        }

    } while (x0free || y0free || x1free || y1free );

    *px0 = x0;
    *py0 = y0;
    *px1 = x1;
    *py1 = y1;
}

#endif